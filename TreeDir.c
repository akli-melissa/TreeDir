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
