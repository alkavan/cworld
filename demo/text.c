#include "text.h"

/**
 * Create text surface with string and color
 *
 * @param t
 * @param string
 * @param color
 */
static void update(Text *const t, const char* string, SDL_Color color) {
    t->surface = TTF_RenderText_Solid(t->font, string, color);

    if ( ! t->surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create text surface (%s)", TTF_GetError());
    }
}

/**
 * Create texture, render it, and free texture and surface
 *
 * @param t
 * @param renderer
 */
static void render(Text *const t, SDL_Renderer *renderer) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, t->surface);
    SDL_Rect dest = {
            t->position.x,
            t->position.y,
            t->surface->w,
            t->surface->h
    };
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(t->surface);
}

Text *text_new(int x, int y, TTF_Font *const font) {
    Text *text = (Text*) malloc(sizeof(Text));

    text->update = &update;
    text->render = &render;

    SDL_Point position = {x, y};
    text->position = position;
    text->font = font;

    return text;
}

void text_free(Text *t) {
    free(t);
}