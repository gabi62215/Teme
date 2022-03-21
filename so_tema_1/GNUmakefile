build: tema1.o structures.o
	gcc tema1.o structures.o -o so-cpp -g

tema1.o: tema1.c
	gcc -c tema1.c -Wall -o tema1.o -g

structues.o: structures.c
	gcc -c structures.c -Wall -o structures.o -g

clean: 
	rm tema1.o structures.o so-cpp
