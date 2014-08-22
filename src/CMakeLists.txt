cmake_minimum_required(VERSION 2.8)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)

project(ld30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES
	main.cpp
	Node.cpp
	Renderer.cpp
	Sprite.cpp
	StateHandler.cpp

	states/GameState.cpp
	states/SplashState.cpp

	ui/Label.cpp
)

set(HEADERS
	IState.h
	Node.h
	Renderer.h
	Sprite.h
	StateHandler.h

	states/GameState.h
	states/SplashState.h

	ui/Label.h
)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
