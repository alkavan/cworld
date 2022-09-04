cmake_minimum_required(VERSION 3.23)
project(cworld LANGUAGES C VERSION 0.1.0)

configure_file(version_config.h.in ${CMAKE_BINARY_DIR}/generated/version_config.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

set(CMAKE_C_STANDARD 17)

# mathc library
add_library(mathc third_party/mathc/mathc.h third_party/mathc/mathc.c)
include_directories(third_party/mathc)

# cworld library
include_directories(include)

add_library(cworld SHARED
        src/cworld.c
        src/cparticle.c
        src/shapes.c
        src/cbody.c
        )

target_link_libraries(cworld mathc)
add_subdirectory(demo)

# copy mandatory assets
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
