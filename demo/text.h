#ifndef SDL2_C17_TEXT_H
#define SDL2_C17_TEXT_H

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>

struct Text {
    struct {
        void (*update)(struct Text *const, const char* string, SDL_Color color);
        void (*render)(struct Text *const, SDL_Renderer *renderer);
    };

    SDL_Point position;
    TTF_Font* font;
    SDL_Surface* surface;
};

typedef struct Text Text;

Text *text_new(int x, int y, TTF_Font *t);
void text_free(Text *t);

#endif //SDL2_C17_TEXT_H
