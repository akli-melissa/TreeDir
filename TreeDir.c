#include "commandes.h"
#include <string.h>
#include <stdio.h>


int main(int argc, char **argv){

    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        perror("file : ");
        exit(-1);
    }
    char *arg = malloc(SIZE);
    init();
    while (fgets(arg, SIZE, file)){
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
        }else if (strcmp(argvs[0], "rm") == 0){
            rm(argvs[1]);
        }else if (strcmp(argvs[0], "exit") == 0){
            break;
        }else if (strcmp(argvs[0], "cp") == 0){
            cp(argvs[1], argvs[2]);
        }else if (strcmp(argvs[0], "mv") == 0){
            mv(argvs[1], argvs[2]);
        }
        else{
            printf("Erreur dans la commande\n");
        }
        if (argvs) free_2d_array(argvs);
    }
    freeAll();
    free(arg);
    exit(0);
}
