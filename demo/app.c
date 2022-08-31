#include "app.h"

#include <SDL2/SDL_ttf.h>

App *app_new() {
    App *app = (App*) malloc(sizeof(App));

    app->renderer = NULL;
    app->window = NULL;
    app->running = true;

    sprintf(app->window_title, "");

    return app;
}

void app_free(App *t) {
    SDL_DestroyRenderer(t->renderer);
    SDL_DestroyWindow(t->window);
    free(t);
}

int app_init(App *const app, const char* title, const char* version, int32_t width, int32_t height)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_CAPTURE;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to init application (%s)", SDL_GetError());
        return EXIT_FAILURE;
    }

    // extract to format?
    sprintf(app->window_title, "%s v%s", title, version);

    app->window = SDL_CreateWindow(app->window_title,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width,
                                   height,
                                   windowFlags
                                   );
    if (!app->window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create window (%s)", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);
    if (!app->renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to create renderer (%s)", SDL_GetError());
        SDL_DestroyWindow(app->window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    if (TTF_Init() != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failed to init font component (%s)", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void app_quit(App *app) {
    app_free(app);
    SDL_Quit();
}
