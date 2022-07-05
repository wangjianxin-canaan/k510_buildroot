################################################################
#
# ko_hello_world
#
################################################################
KO_HELLO_WORLD_VERSION = 1.0
KO_HELLO_WORLD_SITE_METHOD = local
KO_HELLO_WORLD_SITE = $(BR2_EXTERNAL_K510_PATH)/package/ko_hello_world/src
KO_HELLO_WORLD_LICENSE = GPL-2.0
KO_HELLO_WORLD_LICENSE_FILES = LICENSE

define KO_HELLO_WORLD_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/ko_hello_world.ko $(TARGET_DIR)/app/ko_hello_wrold/ko_hello_world.ko
endef

$(eval $(kernel-module))
$(eval $(generic-package))
