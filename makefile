CC = g++

OBJECTS = Runner.cpp

OBJECTS_OUT = Runner.o

CFLAGS = -Wall

INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system

all: $(OBJECTS)
	$(CC) -c $(OBJECTS)
	$(CC) $(OBJECTS_OUT) -o runner $(INCLUDES)