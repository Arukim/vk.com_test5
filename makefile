all: dictsearch

dictsearch: dictsearch.o avl_tree.o
	gcc -o dictsearch dictsearch.o avl_tree.o

avl_tree.o: avl_tree.c
	gcc -c avl_tree.c

dictsearch.o: dictsearch.c
	gcc -c dictsearch.c

clean:
	rm -f dictsearch.o dictsearch avl_tree.o
