cmake_minimum_required(VERSION 2.8)
project(new_space C)

set(
    source
    src/config/conf.c
    src/config/map.c
    src/config/path.c
    src/config/time.c
    src/config/font.c
    src/utility/vector.c
    src/utility/direction.c
    src/components/physics.c
    src/components/drawquad.c
    src/components/drawpos.c
    src/components/sprite.c
    src/components/textbox.c
    src/components/timer.c
    src/actions/movefwd.c
    src/actions/turndir.c
    src/actions/autodie.c
    src/actions/gravity.c
    src/actions/collide.c
    src/actions/shootit.c
    src/actions/animate.c
    src/controllers/space.c
    src/window.c
    src/action.c
    src/entity.c
    src/input.c
    src/factory.c
    src/game.c
    src/main.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g -O0 -std=c89 -pedantic-errors")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

add_executable(game ${source})

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    src)

target_link_libraries(
    game
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    m)

configure_file(data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data COPYONLY)
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})


