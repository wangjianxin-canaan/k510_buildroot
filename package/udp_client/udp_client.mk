################################################################################
#
# udp_client
#
################################################################################

UDP_CLIENT_SITE = $(BR2_EXTERNAL_K510_PATH)/package/udp_client/src
UDP_CLIENT_SITE_METHOD = local
UDP_CLIENT_INSTALL_STAGING = YES

define UDP_CLIENT_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define UDP_CLIENT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/udp.out $(TARGET_DIR)/app/udp_client/udp.out
	$(INSTALL) -D -m 0755 $(@D)/udp.sh $(TARGET_DIR)/app/udp_client/udp.sh
endef

$(eval $(generic-package))
