find_package(SDL2 REQUIRED CONFIG)

add_executable(cworld_demo
        main.c
        config.h
        app.c
        app.h
        draw.c
        draw.h
        input.c
        input.h
        timer.c
        timer.h
        profile.c
        profile.h
        text.c
        text.h
        utility.c utility.h)

target_link_libraries(cworld_demo cworld m SDL2 SDL2_ttf)
