#OBJS specifies which files to compile
OBJS = main.c AGE_Core.c AGE_Sprite.c AGE_Timer.c AGE_Keyboard_Input.c AGE_Mouse_Input.c AGE_List.c AGE_Rectangle.c AGE_SpriteBatch.c AGE_Vector.c AGE_Helper.c AGE_Animation.c

#CC specifies which compiler we're using
CC = gcc

#compiler flags
# -w supress warnings
COMPILER_FLAGS = -w

#error log
ERROR_LOG = log.txt

#LINKER FLAGS for libraries
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm

#obj name for the name of the exe
OBJ_NAME = myGame

# this is the compile line

all : $(OBJS) 
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 2> $(ERROR_LOG) && ./$(OBJ_NAME)
