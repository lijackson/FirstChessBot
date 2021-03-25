CC = g++

OBJECTS = Runner.cpp GameBoard.cpp
OBJECTS_OUT = Runner.o GameBoard.o

TEST_OBJECTS = tests.cpp Runner.cpp GameBoard.cpp
TEST_OBJECTS_OUT = tests.o Runner.o GameBoard.o

CFLAGS = -Wall

INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system

#HEADERS = tests.h Runner.h GameBoard.h

all: $(OBJECTS)
	$(CC) -c $(OBJECTS)
	$(CC) $(OBJECTS_OUT) -o runner $(INCLUDES)

test:
	$(CC) -c $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS_OUT) -o testing $(INCLUDES) $(HEADERS)