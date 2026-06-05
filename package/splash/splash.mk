SPLASH_VERSION = 1.0
SPLASH_SITE = $(TOPDIR)/package/splash/src
SPLASH_SITE_METHOD = local
SPLASH_DEPENDENCIES = sdl2 sdl2_ttf sdl2_mixer sdl2_image

define SPLASH_BUILD_CMDS
    $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define SPLASH_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/splash $(TARGET_DIR)/usr/bin/splash
endef

$(eval $(generic-package))
