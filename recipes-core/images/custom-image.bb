SUMMARY = "My custom image"

IMAGE_INSTALL = "packagegroup-core-boot ${CORE_IMAGE_EXTRA_INSTALL}"
IMAGE_INSTALL:append = " i2c-tools"

IMAGE_LINGUAS = " "

LICENSE = "MIT"

inherit core-image
inherit extrausers

IMAGE_OVERHEAD_FACTOR ?= "1.0"
IMAGE_ROOTFS_SIZE ?= "204800"

# Change root password, not working, try encrypted pass next time


#EXTRA_USERS_PARAMS = "\
#	usermod -P 'toor' root; \
#	"
IMAGE_INSTALL += "bmeapp"
