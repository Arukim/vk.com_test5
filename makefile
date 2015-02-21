CFLAGS = -Wall

all: dictsearch

debug: CFLAGS += -ggdb3
debug: all

dictsearch: dictsearch.o avl_tree.o
	gcc $(CFLAGS) dictsearch.o avl_tree.o -o dictsearch

avl_tree.o: avl_tree.c
	gcc -c $(CFLAGS) avl_tree.c

dictsearch.o: dictsearch.c
	gcc -c $(CFLAGS) dictsearch.c

clean:
	rm -f dictsearch.o dictsearch avl_tree.o
