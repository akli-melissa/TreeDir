#include "commandes.h"
#include <string.h>
#include <stdio.h>
char *get_name(char *chaine){
    while (chaine && *chaine != ' '){
        chaine++;
    }
    while (chaine && *chaine == ' '){
        chaine++;
    }
    if (chaine == NULL){
        printf("Erreur deuxieme arg\n");
        return NULL;
        }
    return chaine;
}

char *get_commande(char *nom){
    char *sauv = nom;
    int cpt =0;
    while (nom && (strcmp(nom  ," ") != 0)){
        nom++;
        cpt++;
    }
    char *result = malloc(sizeof(char)*size);
    strncpy(result, sauv, cpt-1);
    result[cpt]= '\0';
    return result;
}

//mkdir aaaa

int main(){
    char *arg = malloc(sizeof(char)*size);
    init();
    while (1){
        printf("> ");
        fgets(arg, size, stdin);
        char * position;
        position=strchr(arg,'\n');
        if (position!=NULL)
        {
            *position='\0';
        }
        printf("%s\n", arg);
        size_t  nbargv;
        char ** argvs = str_split(arg, ' ', &nbargv);
         printf("%s %s  %d\n",argvs[0], argvs[1], nbargv);
        char *commande=malloc(sizeof(char)*size);
        strcpy(commande ,argvs[0]);
        //  strcpy(commande ,rgv[0]);

        /**
         * essaye d'utiliser une fonction split ici pour construire un tableau d'arguments 
         * split prend e argument une chaine et un dilimiteur pour couper ta chaine dans ce cas 
         * c'est l'espace
         * comme ça argv[0] qui répresente la première case de ton tableau sera la commande 
         * et argv[1] qui représente la deuxième case sera la première optien
         * si tu as besin d'explication just call bissssss 
         */
        if (strcmp(commande, "mkdir") == 0){
            printf("i'm making a dir \n");
            mkdir(argvs[1]);
            //  mkdir(argv[1]);
        }
        else if (strcmp(commande, "cd") == 0){
            printf("i'm changing th dir\n");
            cd(argvs[1]);

        }
        else if (strcmp(commande, "pwd") == 0){
            printf("where i'm");
            pwd();
        }
        else{
            printf("Erreur dans la commande\n");
        }
        free(commande);
    }
    free(arg);
    exit(0);
}