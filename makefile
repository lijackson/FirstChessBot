OBJECTS = Renderer.cpp GameBoard.cpp ChessAI.cpp
OBJECTS_OUT = Renderer.o GameBoard.o ChessAI.o

TEST_OBJECTS = tests.cpp Renderer.cpp GameBoard.cpp ChessAI.cpp debugstuff.cpp
TEST_OBJECTS_OUT = tests.o Renderer.o GameBoard.o ChessAI.o debugstuff.o

INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system



CC=g++

ODIR=obj

CFLAGS=-Wall
FLAGS=-O3

$(ODIR)/%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

_OBJS = Renderer GameBoard ChessAI debugstuff main
OBJS = $(patsubst %, $(ODIR)/%.o, $(_OBJS))
chessai: $(OBJS)
	$(CC) $(FLAGS) -o chessai $(OBJS) $(CFLAGS) $(INCLUDES)

.PHONY:
	clean

clean:
	rm -f $(ODIR)/*.o