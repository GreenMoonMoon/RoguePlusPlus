cmake_minimum_required(VERSION 3.23)
project(rpp)
set(CMAKE_CXX_STANDARD 20)

set(flecs_INCLUDE_DIR external/flecs)
set(flecs_SOURCE_FILES external/flecs/flecs.c)

set(glad_INCLUDE_DIR external/glad/include)
set(glad_SOURCE_FILES
        external/glad/src/gl.c)

set(glm_INCLUDE_DIR external/glm)

set(sdl_INCLUDE_DIR external/SDL2/include)
set(sdl_LIBRARY_DIR external/SDL2/lib/x64)

set(stb_INCLUDE_DIR external/stb)

include_directories(
        ${flecs_INCLUDE_DIR}
        ${glad_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}
        ${sdl_INCLUDE_DIR}
        ${stb_INCLUDE_DIR})

link_directories(
        ${sdl_LIBRARY_DIR})

set(rpp_SOURCE_FILES
        main.cpp

        graphics/camera.cpp
        graphics/mesh.cpp
        graphics/model.cpp
        graphics/renderer.cpp
        graphics/shader.cpp
        graphics/textures.cpp

        inputs/inputs.cpp)

add_executable(rpp)
target_sources(rpp PRIVATE
        ${rpp_SOURCE_FILES}
        ${flecs_SOURCE_FILES}
        ${glad_SOURCE_FILES})
target_link_libraries(rpp PRIVATE SDL2 SDL2main)
target_compile_definitions(rpp PRIVATE SDL_OPENGL_GRAPHICS)

add_custom_command(TARGET rpp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PROJECT_SOURCE_DIR}/${sdl_LIBRARY_DIR}/SDL2.dll
        $<TARGET_FILE_DIR:rpp>)