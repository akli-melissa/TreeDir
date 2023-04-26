TreeDir.o : TreeDir.c
	gcc -Wall *.c -o TreeDir

commandes.o : commandes.c
	gcc -o commandes.o -c commandes.c

clean:
	rm *.o