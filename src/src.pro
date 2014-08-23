######################################################################
# Automatically generated by qmake (3.0) Fri Aug 22 06:23:54 2014
######################################################################

TEMPLATE = app
TARGET = ld30
INCLUDEPATH += . states ui
CONFIG += c++11
LIBS += -lSDL2 -lSDL2_ttf -lSDL2_image

# Input
HEADERS += IState.h \
           Node.h \
           Renderer.h \
           Sprite.h \
           states/GameState.h \
           states/SplashState.h \
           ui/Label.h \
    StateHandler.h \
    IDrawable.h \
    states/MenuState.h \
    states/MainMenuState.h \
    states/MenuItem.h \
    states/SettingsMenuState.h \
	states/ResolutionMenuState.h \
	StringEx.h \
	BinaryStream.h \
    SettingsHandler.h \
	Settings.h \
	ISettingsProvider.h \
	DefaultSettingsProvider.h \
	SettingsProvider.h \
    Level.h \
    ImageWrapper.h \
    LevelTile.h \
    LevelTileLayer.h \
    LevelTileMapObject.h \
    drawables/Spawn.h \
    drawables/Goal.h \
	Util.h \
	PathFinder.h \
	PathNode.h \
	DereferencedEqual.h \
	DereferencedLess.h

SOURCES += main.cpp \
           Node.cpp \
           Renderer.cpp \
           Sprite.cpp \
           states/GameState.cpp \
           states/SplashState.cpp \
		   ui/Label.cpp \
    StateHandler.cpp \
    states/MainMenuState.cpp \
    states/MenuItem.cpp \
    states/MenuState.cpp \
    states/SettingsMenuState.cpp \
	states/ResolutionMenuState.cpp \
	StringEx.cpp \
	BinaryStream.cpp \
    SettingsHandler.cpp \
	Settings.cpp \
	DefaultSettingsProvider.cpp \
	SettingsProvider.cpp \
    Level.cpp \
    ImageWrapper.cpp \
    LevelTile.cpp \
    LevelTileLayer.cpp \
    LevelTileMapObject.cpp \
    drawables/Spawn.cpp \
	drawables/Goal.cpp \
	PathFinder.cpp \
	PathNode.cpp
