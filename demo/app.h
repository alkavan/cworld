#ifndef SDL2_C17_APP_H
#define SDL2_C17_APP_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define COLOR_RED   (SDL_Color){255, 0,   0  }
#define COLOR_GREEN (SDL_Color){0,   255, 0  }
#define COLOR_BLUE  (SDL_Color){0,   0,   255}
#define COLOR_WHITE (SDL_Color){255, 255, 255}
#define COLOR_BLACK (SDL_Color){0,   0,   0  }

struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;
    bool running;
    char window_title[255];
};

typedef struct App App;

App *app_new();
void app_free(App *t);

int app_init(App * app, const char* title, const char* version, int32_t width, int32_t height);
void app_quit(App *app);

#endif //SDL2_C17_APP_H
