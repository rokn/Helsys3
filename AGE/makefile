#AGE engine files
AGE = AGE_Core.c AGE_Sprite.c AGE_Timer.c AGE_Keyboard_Input.c AGE_Mouse_Input.c AGE_List.c AGE_Rectangle.c AGE_SpriteBatch.c AGE_Vector.c AGE_Helper.c AGE_Animation.c

#AGE objects
AGE_OBJS = AGE_Core.o AGE_Sprite.o AGE_Timer.o AGE_Keyboard_Input.o AGE_Mouse_Input.o AGE_List.o AGE_Rectangle.o AGE_SpriteBatch.o AGE_Vector.o AGE_Helper.o AGE_Animation.o

#CC specifies which compiler we're using
CC = gcc

#compiler flags
# -w supress warnings
COMPILER_FLAGS = -w -c

#error log
ERROR_LOG = log.txt

#LINKER FLAGS for libraries
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm


all : $(AGE)
	$(CC) $(COMPILER_FLAGS) $(AGE) $(LINKER_FLAGS) 2> $(ERROR_LOG) && ar rcs libAGE.a $(AGE_OBJS) && rm *.o && beep