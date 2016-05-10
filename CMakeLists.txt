cmake_minimum_required(VERSION 2.8)
project(new_space C)

set(
    source
    src/utility/vector.c
    src/utility/entity.c
    src/components/physics.c
    src/entities/planet.c
    src/main.c
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -g -O0 -std=c89 -pedantic-errors")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

add_executable(space ${source})

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2_TTF REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    src)

target_link_libraries(
    space
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    m)

