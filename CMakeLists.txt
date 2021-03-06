cmake_minimum_required(VERSION 3.10)
project(new_space C)

set(
    SOURCE_FILES
    src/config/conf.c
    src/config/map.c
    src/config/path.c
    src/config/time.c
    src/config/font.c
    src/config/glob.c
    src/utility/string.c
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
    src/controllers/gameplay.c
    src/controllers/pressstart.c
    src/controllers/chooseyourcat.c
    src/scenes/gameplay.c
    src/scenes/pressstart.c
    src/scenes/chooseyourcat.c
    src/window.c
    src/scene.c
    src/action.c
    src/sound.c
    src/entity.c
    src/input.c
    src/debug.c
    src/game.c
    src/main.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g -O0 -std=c89 -pedantic-errors")
if (DEBUG_MODE)
    message("Debug mode set to true")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG_MODE")
endif(DEBUG_MODE)
if (NO_MUSIC)
    message("No music mode set to true")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNO_MUSIC")
endif(NO_MUSIC)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

add_executable(SpaceCats ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(SDL2_MIXER REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_MIXER_INCLUDE_DIR}
    src)

target_link_libraries(
    SpaceCats
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    m)

configure_file(data ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data COPYONLY)
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
