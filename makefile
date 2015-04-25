#OBJS specifies which files to compile
OBJS = main.c battlefield.c tiles.c battle_entity.c

#CC specifies which compiler we're using
CC = gcc

#compiler flags
# -w supress warnings
COMPILER_FLAGS = -Wall -g

#error log
ERROR_LOG = log.txt

#LINKER FLAGS for libraries
LINKER_FLAGS = -L./AGE -lAGE -lSDL2 -lSDL2_image -lSDL2_ttf -lm

#obj name for the name of the exe
OBJ_NAME = GAME

# this is the compile line

all : $(OBJS) 
	$(CC) $(OBJS) $(AGE) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 2> $(ERROR_LOG) && ./$(OBJ_NAME)

install :
	apt-get install libsdl2-2.0-0 && apt-get install libsdl2-image-2.0-0 &&  apt-get install libsdl2-ttf-2.0-0