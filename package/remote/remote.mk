REMOTE_VERSION = 1.0
REMOTE_SITE = $(TOPDIR)/package/remote/src
REMOTE_SITE_METHOD = local

define REMOTE_BUILD_CMDS
    $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define REMOTE_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/remote $(TARGET_DIR)/usr/bin/remote
endef

$(eval $(generic-package))
