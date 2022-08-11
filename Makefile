OBJECT_DIRECTORY = .\src

#OBJS specifies which files to compile as part of the project
_OBJS = main.cpp Game.cpp GameState.cpp Sprite.cpp Music.cpp GameObject.cpp Sound.cpp Face.cpp TileSet.cpp TileMap.cpp Resources.cpp InputManager.cpp Camera.cpp

OBJS = $(patsubst %,$(OBJECT_DIRECTORY)/%,$(_OBJS))

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\SDL2\include\SDL2 -I.\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\SDL2\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -std=c++17 -Wall -Wextra -pedantic -Wl,-subsystem,windows

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

#This is the target that compiles our executable
game : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@