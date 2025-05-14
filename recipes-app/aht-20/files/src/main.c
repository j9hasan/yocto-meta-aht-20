#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#define AHT20_ADDR         0x38
#define AHT20_I2C_BUS      "/dev/i2c-0"

int main() {
    int fd = open(AHT20_I2C_BUS, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C bus");
        return -1;
    }

    if (ioctl(fd, I2C_SLAVE, AHT20_ADDR) < 0) {
        perror("Failed to connect to AHT20");
        close(fd);
        return -1;
    }

    // Step 1: Wait 40 ms after power-on
    usleep(40000);

    // Step 2: Check calibration status (0x71)
    uint8_t cmd_status = 0x71;
    write(fd, &cmd_status, 1);
    uint8_t status;
    read(fd, &status, 1);

    if ((status & 0x08) == 0) {
        // Not calibrated -> send initialization command: 0xBE 0x08 0x00
        uint8_t init_cmd[] = {0xBE, 0x08, 0x00};
        write(fd, init_cmd, sizeof(init_cmd));
        usleep(10000);
    }

    // Step 3: Send measurement command: 0xAC 0x33 0x00
    uint8_t measure_cmd[] = {0xAC, 0x33, 0x00};
    if (write(fd, measure_cmd, sizeof(measure_cmd)) != sizeof(measure_cmd)) {
        perror("Failed to write measurement command");
        close(fd);
        return -1;
    }

    usleep(80000);  // Wait for measurement to complete

    // Step 4: Read 6 bytes + 1 byte CRC (optional)
    uint8_t data[7];
    if (read(fd, data, 7) != 7) {
        perror("Failed to read data");
        close(fd);
        return -1;
    }

    // Check if measurement is done (bit 7 == 0)
    if (data[0] & 0x80) {
        fprintf(stderr, "Measurement not completed yet.\n");
        close(fd);
        return -1;
    }

    // Step 5: Parse data
    uint32_t raw_humidity = ((uint32_t)data[1] << 12) |
                             ((uint32_t)data[2] << 4) |
                             ((data[3] & 0xF0) >> 4);

    uint32_t raw_temperature = ((uint32_t)(data[3] & 0x0F) << 16) |
                                ((uint32_t)data[4] << 8) |
                                ((uint32_t)data[5]);

    float humidity = (raw_humidity * 100.0) / 1048576.0;     // 2^20 = 1048576
    float temperature = ((raw_temperature * 200.0) / 1048576.0) - 50.0;

    printf("Humidity: %.2f %%\n", humidity);
    printf("Temperature: %.2f °C\n", temperature);

    close(fd);
    return 0;
}
