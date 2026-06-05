#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define SCREEN_W   960
#define SCREEN_H   540
#define SPLASH_MS  4000

#define IMAGE_PATH "/usr/share/arcade/splash.bmp"
#define SOUND_PATH "/usr/share/arcade/splash.wav"
#define FONT_PATH "/usr/share/fonts/pixeldroidConsoleRegularMono.ttf"

int main(void) {
    SDL_Log("splash: starting");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
    else
        SDL_Log("SDL_Init OK");

    TTF_Init();

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
    else
        SDL_Log("Mix_OpenAudio OK");

    SDL_Window *win = SDL_CreateWindow("",
        0, 0, SCREEN_W, SCREEN_H, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (!win)
        SDL_Log("CreateWindow failed: %s", SDL_GetError());
    else
        SDL_Log("CreateWindow OK");

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren)
        SDL_Log("CreateRenderer failed: %s", SDL_GetError());
    else
        SDL_Log("CreateRenderer OK");

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);
    SDL_Log("black frame presented");

    SDL_Log("loading BMP: %s", IMAGE_PATH);
    SDL_Surface *img = SDL_LoadBMP(IMAGE_PATH);
    if (!img) {
        SDL_Log("SDL_LoadBMP failed: %s", SDL_GetError());

        /* fallback text */
        TTF_Font *font = TTF_OpenFont(FONT_PATH, 72);
        if (!font) {
            SDL_Log("TTF_OpenFont failed: %s", TTF_GetError());
        } else {
            SDL_Log("font loaded OK");
            SDL_Color white = {255, 255, 255, 255};
            SDL_Surface *s = TTF_RenderUTF8_Blended(font, "ARCADE", white);
            SDL_Texture *t = SDL_CreateTextureFromSurface(ren, s);
            SDL_Rect r = {(SCREEN_W - s->w) / 2, (SCREEN_H - s->h) / 2, s->w, s->h};
            SDL_RenderCopy(ren, t, NULL, &r);
            SDL_FreeSurface(s);
            SDL_DestroyTexture(t);
            TTF_CloseFont(font);
        }
    } else {
        SDL_Log("BMP loaded OK: %dx%d", img->w, img->h);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, img);
        if (!tex) {
            SDL_Log("CreateTextureFromSurface failed: %s", SDL_GetError());
        } else {
            SDL_Log("texture created OK");
            float scale = (float)SCREEN_W / img->w;
            if (img->h * scale > SCREEN_H) scale = (float)SCREEN_H / img->h;
            SDL_Rect dst = {
                (SCREEN_W - (int)(img->w * scale)) / 2,
                (SCREEN_H - (int)(img->h * scale)) / 2,
                (int)(img->w * scale),
                (int)(img->h * scale)
            };
            SDL_Log("dst rect: %d %d %d %d", dst.x, dst.y, dst.w, dst.h);
            int rc = SDL_RenderCopy(ren, tex, NULL, &dst);
            SDL_Log("RenderCopy result: %d", rc);
            SDL_DestroyTexture(tex);
        }
        SDL_FreeSurface(img);
    }

    SDL_RenderPresent(ren);
    SDL_Log("image frame presented");

    /* play sound */
    Mix_Chunk *sound = Mix_LoadWAV(SOUND_PATH);
    if (!sound)
        SDL_Log("Mix_LoadWAV failed: %s", Mix_GetError());
    else {
        SDL_Log("sound loaded OK");
        Mix_PlayChannel(-1, sound, 0);
    }

    /* wait */
    Uint32 start = SDL_GetTicks();
    SDL_Event ev;
    int skip = 0;
    while (!skip && SDL_GetTicks() - start < SPLASH_MS) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_KEYDOWN    ||
                ev.type == SDL_JOYBUTTONDOWN ||
                ev.type == SDL_QUIT) {
                skip = 1;
                break;
            }
        }
        SDL_Delay(16);
    }

    SDL_Log("splash: done");

    if (sound) Mix_FreeChunk(sound);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
