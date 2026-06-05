CFLAGS += $(shell $(PKG_CONFIG) --cflags sdl2 SDL2_ttf SDL2_mixer SDL2_image)
LIBS    = $(shell $(PKG_CONFIG) --libs   sdl2 SDL2_ttf SDL2_mixer SDL2_image)

splash: splash.c
	$(CC) $(CFLAGS) splash.c -o splash $(LIBS)

clean:
	rm -f splash
