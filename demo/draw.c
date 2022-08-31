#include "draw.h"
#include "config.h"

void prepare_scene(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void present_scene(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}

void draw_debug_line(SDL_Renderer *renderer, SDL_Color color, Vec2 p1, Vec2 p2) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(renderer, p1.x, p1.y, p2.x, p2.y);
}

void draw_debug_point(SDL_Renderer *renderer, SDL_Color color, Vec2 p1) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLineF(renderer, p1.x, p1.y, p1.x, p1.y);
}


void draw_debug_cross(SDL_Renderer *renderer, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(renderer, 0, SCREEN_HALF_HEIGHT, SCREEN_WIDTH, SCREEN_HALF_HEIGHT);
    SDL_RenderDrawLine(renderer, SCREEN_HALF_WIDTH, 0, SCREEN_HALF_WIDTH, SCREEN_HEIGHT);
}

void draw_debug_grid(SDL_Renderer *renderer, SDL_Color color, Vec2i size) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int gx = SCREEN_WIDTH / size.x;
    int gy = SCREEN_HEIGHT / size.y;

    int i, j;
    for(i = 1; i < gx; i++) {
        SDL_RenderDrawLine(renderer, size.x*i, 0, size.x*i, SCREEN_HEIGHT);
        for(j = 1; j < gy; j++) {
            SDL_RenderDrawLine(renderer, 0, size.y*j, SCREEN_WIDTH, size.y*j);
        }
    }
}
