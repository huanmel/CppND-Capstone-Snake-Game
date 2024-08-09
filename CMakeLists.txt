cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(MySnakeSDL)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2/")


find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

# Add subdirectory
# add_subdirectory(nanogui-sdl)

add_executable(${PROJECT_NAME} src/mesq.h src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp src/food.cpp src/cell.cpp src/body2.cpp )
# string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
# target_link_libraries(SnakeGame ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})