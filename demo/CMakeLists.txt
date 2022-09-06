find_package(SDL2 REQUIRED CONFIG)
find_package(sdl2-ttf CONFIG REQUIRED)

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
        utility.c
        utility.h
        )

target_include_directories(cworld_demo PRIVATE "C:\\vcpkg\\installed\\x86-windows\\include")

target_link_libraries(cworld_demo cworld SDL2::SDL2 SDL2::SDL2main SDL2::SDL2_ttf)
