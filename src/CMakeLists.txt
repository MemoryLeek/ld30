cmake_minimum_required(VERSION 2.8)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)

project(ld30)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../bin")

set(SOURCES
	main.cpp
	Node.cpp
	Renderer.cpp
	Sprite.cpp
	StateHandler.cpp
	StringEx.cpp
	BinaryStream.cpp
	Settings.cpp
	SettingsHandler.cpp
	DefaultSettingsProvider.cpp
	SettingsProvider.cpp
	Level.cpp
	LevelTile.cpp
	ImageWrapper.cpp
	LevelTileLayer.cpp
	LevelTileMapObject.cpp
	Player.cpp
	CollisionHandler.cpp
	SoundHandler.cpp
	SpriteBundle.cpp
	SpriteBundleSprite.cpp
	SpriteLoader.cpp

	states/GameState.cpp
	states/SplashState.cpp
	states/MenuState.cpp
	states/MainMenuState.cpp
	states/MenuItem.cpp
	states/SettingsMenuState.cpp
	states/ResolutionMenuState.cpp
	states/SoundVolumeMenuState.cpp
	
	drawables/Goal.cpp
	drawables/Spawn.cpp
	drawables/Scoreboard.cpp

	ui/Label.cpp
)

set(HEADERS
	IState.h
	Node.h
	Renderer.h
	Sprite.h
	StateHandler.h
	StringEx.h
	BinaryStream.h
	ISettingsProvider.h
	Settings.h
	SettingsHandler.h
	DefaultSettingsProvider.h
	SettingsProvider.h
	Level.h
	LevelTile.h
	ImageWrapper.h
	LevelTileLayer.h
	LevelTileMapObject.h
	Player.h
	Util.h
	CollisionHandler.h
	SoundHandler.h
	SpriteBundle.h
	SpriteBundleSprite.h
	SpriteLoader.h

	states/GameState.h
	states/SplashState.h
	states/MenuState.h
	states/MainMenuState.h
	states/MenuItem.h
	states/SettingsMenuState.h
	states/ResolutionMenuState.h
	states/SoundVolumeMenuState.h
	
	drawables/Goal.h
	drawables/Spawn.h
	drawables/Scoreboard.h

	ui/Label.h
)

include_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

# Hacks for crap OS
if(WIN32)
	add_definitions(-DM_PI=3.14159265358979323846)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mwindows")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()
