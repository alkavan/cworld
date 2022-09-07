#ifndef SDL2_C17_DRAW_H
#define SDL2_C17_DRAW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cworld/types.h>

void prepare_scene(SDL_Renderer *renderer);
void present_scene(SDL_Renderer *renderer);

void draw_debug_point(SDL_Renderer *renderer, SDL_Color color, Vec2 p1);
void draw_debug_line(SDL_Renderer *renderer, SDL_Color color, Vec2 p1, Vec2 p2);
void draw_debug_rect(SDL_Renderer *renderer, SDL_Color color, Vec2 p1, Vec2 size, float angle);
void draw_debug_cross(SDL_Renderer *renderer, SDL_Color color);
void draw_debug_grid(SDL_Renderer *renderer, SDL_Color color, Vec2i size);

#endif //SDL2_C17_DRAW_H
