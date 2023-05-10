cmake_minimum_required(VERSION 3.2.0)
project(myTetris VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

# OpenGL
find_package(OpenGL REQUIRED) 
message(STATUS "OPENGL included at ${OPENGL_INCLUDE_DIR}")
message(STATUS "OPENGL libraries at ${OPENGL_LIBRARIES}")

# SDL2
find_package(SDL2 REQUIRED COMPONENTS SDL2)
message(STATUS "SDL2 included at ${SDL_INCLUDE_DIRS}")
message(STATUS "SDL2 libraries at ${SDL_LIBRARIES}")

# SDL2 Image
find_package(SDL2_image REQUIRED)
message(STATUS "SDL2_image included at ${SDLIMAGE_INCLUDE_DIR}")
message(STATUS "SDL2_image libraries at ${SDLIMAGE_LIBRARY}")

# SDL2 ttf
find_package(SDL2_TTF REQUIRED)
message(STATUS "SDL2_ttf included at ${SDLTTF_INCLUDE_DIR}")
message(STATUS "SDL2_ttf libraries at ${SDLTTF_LIBRARY}")


add_executable (${CMAKE_PROJECT_NAME} src/tetris.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR} ${SDLTTF_INCLUDE_DIR})
target_link_libraries (${CMAKE_PROJECT_NAME} ${SDL_LIBRARIES} SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf ${OPENGL_LIBRARIES} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY})