CC = g++
FLAGS = -g -Wall

DEPS = definitions.h functions.h variables.h
OBJ = functions.o variables.o main.o

all: underdogs

build: underdogs

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

underdogs: $(OBJ)
	$(CC) $(CFLAGS) $^ -o underdogs

run: build
	./underdogs

xboard: build
	xboard -fcp "make run" -debug

.PHONY: clean

clean: 
	rm -f *.o underdogs xboard.debug