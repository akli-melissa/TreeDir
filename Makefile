run:TreeDir
	./TreeDir

TreeDir : TreeDir.o commandes.o
	gcc -o TreeDir TreeDir.o commandes.o

TreeDir.o : commandes.o
	gcc -c -Wall TreeDir.c

commandes.o : commandes.h
	gcc -c -Wall commandes.c

clean:
	rm *.o