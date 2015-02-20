all: dictsearch.exe

dictsearch.exe: dictsearch.o
	gcc -o dictsearch.exe dictsearch.o

dictsearch.o: main.c
	gcc -c -o dictsearch.o main.c

clean:
	rm dictsearch.o dictsearch.exe
