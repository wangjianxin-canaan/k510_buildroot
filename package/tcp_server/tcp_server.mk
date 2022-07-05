################################################################################
#
# tcp_server
#
################################################################################

TCP_SERVER_SITE = $(BR2_EXTERNAL_K510_PATH)/package/tcp_server/src
TCP_SERVER_SITE_METHOD = local
TCP_SERVER_INSTALL_STAGING = YES

define TCP_SERVER_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) 
endef

define TCP_SERVER_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/tcp_server $(TARGET_DIR)/app/tcp_server/tcp_server
endef

$(eval $(generic-package))
