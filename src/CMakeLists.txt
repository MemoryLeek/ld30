cmake_minimum_required(VERSION 2.8)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)

project(ld30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES
	main.cpp
	Window.cpp
)

set(HEADERS
	Window.h
)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${BOX2D_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
