# Which compile to use
CC = g++

# === DIRECTORY LOCATIONS =======================

# Where to find the include folder
INCLUDE_DIRECTORY = ../include

# Where to find the objects folder
OBJECT_DIRECTORY = obj

# SDL Include Directory
SDL_INCLUDE = $(shell sdl2-config --cflags)

# SDL Library Directory
SDL_LIBRARY = $(shell sdl2-config --libs)

# === ARGUMENTS ================================

# Which libraries to include
LIBS = -l SDL2-2.0.0

# Additional compilation arguments
COMPILER_FLAGS = -std=c++17 -Wall -Wextra -pedantic

# Compilation arguments
COMPILATION_ARGS = -I $(INCLUDE_DIRECTORY) $(SDL_INCLUDE) $(COMPILER_FLAGS)

# === FILES ===================================

# Header files
_DEPS = Game.h

# Generate header filepaths
DEPS = $(patsubst %,$(INCLUDE_DIRECTORY)/%,$(_DEPS))

# Object files
_OBJS = main.o Game.o

# Generate object filepaths
OBJS = $(patsubst %,$(OBJECT_DIRECTORY)/%,$(_OBJS))

# === RULES ===================================

# Define how to make .o files, and make them dependent on their .c counterparts and the h files
$(OBJECT_DIRECTORY)/%.o: %.cpp $(DEPS)
	mkdir -p $(OBJECT_DIRECTORY); $(CC) -c -o $@ $< $(COMPILATION_ARGS)
	
# Makes the game
game: $(OBJS)
	$(CC) $^ $(COMPILATION_ARGS) $(LIBS) $(SDL_LIBRARY) -o $@

.PHONY: clean

clean:
	rm -f -r $(OBJECT_DIRECTORY)