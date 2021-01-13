CC = g++
FLAGS = -I
DEPS = Runner.h

ODIR = obj

_OBJ = hellomake.o hellofunc.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: Runner.cpp
	$(CC) -o hellomake Runner.cpp -I.