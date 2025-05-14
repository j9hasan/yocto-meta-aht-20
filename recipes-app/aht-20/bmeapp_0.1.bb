SUMMARY = " Get temp and humidity from sensor"
DESCRIPTION = "Custom recipe to build main.c application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# where to find source files
SRC_URI = "file://src"

# where the downloaded source files (in tmp/work)
S = "${WORKDIR}/src"

# pass argument to linker
TAEGET_CC_ARCH += "${LDFLAGS}"

# cross compile source code
do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} main.c -o aht-20
}


# create usr/bin in rootfs and copy program to it
do_install(){
	install -d ${D}${bindir}
	install -m 0755 aht-20 ${D}${bindir}
}
# 🔧 Tell Yocto what files to package
FILES_${PN} += "${bindir}/aht-20"
