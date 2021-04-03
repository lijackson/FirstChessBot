CC = g++

OBJECTS = Renderer.cpp GameBoard.cpp ChessAI.cpp
OBJECTS_OUT = Renderer.o GameBoard.o ChessAI.o

TEST_OBJECTS = tests.cpp Renderer.cpp GameBoard.cpp ChessAI.cpp debugstuff.cpp
TEST_OBJECTS_OUT = tests.o Renderer.o GameBoard.o ChessAI.o debugstuff.o

CFLAGS = -Wall

INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system

#HEADERS = tests.h Runner.h GameBoard.h

all: $(OBJECTS)
	$(CC) -c $(OBJECTS)
	$(CC) $(OBJECTS_OUT) -o runner $(INCLUDES)

test:
	$(CC) -c $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS_OUT) -o testing $(INCLUDES) $(HEADERS)