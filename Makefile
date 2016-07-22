ifeq ($(OS),Windows_NT)
	OBJS = *.c engine/*.c
	CC = gcc
	INCLUDE_PATHS = -I'C:\mingw_dev_lib\include'
	LIBRARY_PATHS = -L'C:\mingw_dev_lib\lib'
	COMPILER_FLAGS = -w -Wall -g
	LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
	OBJ_NAME = game.exe
else
	OBJS = *.c engine/*.c
	CC = gcc
	LINKER_FLAGS = -lSDL2
	OBJ_NAME = game
endif

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
