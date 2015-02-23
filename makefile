CFLAGS = -Wall

all: dictsearch

debug: CFLAGS += -ggdb3 -DDEBUG
debug: all

dictsearch: dictsearch.o avl_tree.o
	gcc $(CFLAGS) dictsearch.o avl_tree.o -o dictsearch

avl_tree.o: avl_tree.c avl_tree.h
	gcc -c $(CFLAGS) avl_tree.c avl_tree.h

dictsearch.o: dictsearch.c avl_tree.h
	gcc -c $(CFLAGS) dictsearch.c avl_tree.h

clean:
	rm -f dictsearch.o dictsearch avl_tree.o
