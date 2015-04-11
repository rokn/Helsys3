#OBJS specifies which files to compile
OBJS = main.c sprite.c timer.c keyboard_input.c mouse_input.c

#CC specifies which compiler we're using
CC = gcc

#compiler flags
# -w supress warnings
COMPILER_FLAGS = -w

#error log
ERROR_LOG = log.txt

#LINKER FLAGS for libraries
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

#obj name for the name of the exe
OBJ_NAME = myGame

# this is the compile line

all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 2> $(ERROR_LOG) && ./$(OBJ_NAME)