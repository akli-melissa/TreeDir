#include "commandes.h"
#include <string.h>
#include <stdio.h>

int main(){
    char *arg = malloc(SIZE);
    init();
    while (1){
        printf("> ");
        fgets(arg, SIZE, stdin);
        fflush(stdin);
        char ** argvs = split(arg, ' ');
        /**
         * essaye d'utiliser une fonction split ici pour construire un tableau d'arguments 
         * split prend e argument une chaine et un dilimiteur pour couper ta chaine dans ce cas 
         * c'est l'espace
         * comme ça argv[0] qui répresente la première case de ton tableau sera la commande 
         * et argv[1] qui représente la deuxième case sera la première optien
         * si tu as besin d'explication just call bissssss 
         */
        if (strcmp(argvs[0], "mkdir") == 0){
            mkdir(argvs[1]);
        }
        else if (strcmp(argvs[0], "cd") == 0){
            cd(argvs[1]);
        }
        else if (strcmp(argvs[0], "pwd") == 0){
            pwd();
        }
        else if (strcmp(argvs[0], "ls") == 0){
            ls();
        }
        else if (strcmp(argvs[0], "touch") == 0){
            touch(argvs[1]);
        }
        else if (strcmp(argvs[0], "print") == 0){
            print();
        }
        else{
            printf("Erreur dans la commande\n");
        }
        if (argvs) free_2d_array(argvs);
    }
    free(arg);
    exit(0);
}
