################################################################################
#
# tcp_client
#
################################################################################

TCP_CLIENT_SITE = $(BR2_EXTERNAL_K510_PATH)/package/tcp_client/src
TCP_CLIENT_SITE_METHOD = local
TCP_CLIENT_INSTALL_STAGING = YES

define TCP_CLIENT_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define TCP_CLIENT_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/tcp_client $(TARGET_DIR)/app/tcp_client/tcp_client
endef

$(eval $(generic-package))
