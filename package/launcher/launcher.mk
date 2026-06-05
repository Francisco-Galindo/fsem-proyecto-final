LAUNCHER_VERSION = 1.0
LAUNCHER_SITE = $(TOPDIR)/package/launcher/src
LAUNCHER_SITE_METHOD = local
LAUNCHER_DEPENDENCIES = sdl2 sdl2_ttf

define LAUNCHER_BUILD_CMDS
    $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define LAUNCHER_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/launcher $(TARGET_DIR)/usr/bin/launcher
endef

$(eval $(generic-package))
