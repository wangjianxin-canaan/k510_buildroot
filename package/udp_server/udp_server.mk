################################################################################
#
# udp_server
#
################################################################################

UDP_SERVER_SITE = $(BR2_EXTERNAL_K510_PATH)/package/udp_server/src
UDP_SERVER_SITE_METHOD = local
UDP_SERVER_INSTALL_STAGING = YES

define UDP_SERVER_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define UDP_SERVER_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/udp_server $(TARGET_DIR)/app/udp_server/udp_server
endef

$(eval $(generic-package))
