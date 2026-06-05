CFLAGS += $(shell $(PKG_CONFIG) --cflags sdl2 SDL2_ttf)
LIBS    = $(shell $(PKG_CONFIG) --libs   sdl2 SDL2_ttf)

launcher: launcher.c
	$(CC) $(CFLAGS) launcher.c -o launcher $(LIBS)

clean:
	rm -f launcher
