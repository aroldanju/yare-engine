cmake_minimum_required(VERSION 3.14)
project(yare_engine)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(yare_engine src/main.cpp src/sdl/sdlrenderer.cpp src/sdl/sdltexture.cpp src/sdl/sdlfont.cpp src/label.cpp src/sdl/sdleventhandler.cpp src/assetmanager.cpp
        src/map.cpp src/player.cpp)
target_link_libraries(yare_engine -lSDL2 -lSDL2_ttf)