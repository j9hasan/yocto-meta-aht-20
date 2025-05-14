# yocto-meta-aht-20 Layer

This README file contains information on the contents of the **yocto-meta-aht-20** layer.

This layer contains custom recipes and modifications for the BME application and hardware sensor integration using the AHT20 sensor over I2C.

> ✅ **Tested on:** `i2c-bus 0` of **NVIDIA Jetson Nano**

---

## Dependencies

This layer depends on the following layers:

```text
URI: https://git.yoctoproject.org/poky  
branch: kirkstone  

URI: https://git.openembedded.org/meta-openembedded  
branch: kirkstone  

URI: https://github.com/OE4T/meta-tegra.git  # BSP for Jetson Nano board  
branch: kirkstone-l4t-r35.3.1  
```

---

## Table of Contents

I. [Adding the layer to your build](#i-adding-the-layer-to-your-build)
II. [Build the custom image](#ii-build-the-custom-image)
III. [Flash](#iii-flash)
IV. [Run in target device](#iv-run-in-target-device-in-my-case-jetson-nano-board)

---

## I. Adding the layer to your build

Run the following commands from your Yocto build directory:

```bash
cd ../
git clone git@github.com:j9hasan/yocto-meta-aht20.git
cd build
nano conf/bblayers.conf
```

Then add the following line to `bblayers.conf`:

```text
/home/${USER}/yocto-tegra/yocto-meta-aht-20 \
```

---

## II. Build the custom image

```bash
bitbake custom-image
```

---

## III. Flash

Use `dd` or **Balena Etcher** to flash the image to an SD card.

Example using `dd`:

```bash
sudo dd if=custom-image.sdimg of=/dev/sdX bs=4M status=progress && sync
```

> Replace `/dev/sdX` with your actual SD card device.

---

## IV. Run in target device (in my case, Jetson Nano board)

After login, run the following command:

```bash
aht-20
```

This will print the temperature and humidity readings from the AHT20 sensor.

---
