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
        scanf("%s",arg); 
        char *commande=malloc(sizeof(char)*size);
        strcpy(commande ,get_commande(arg));
        /**
         * essaye d'utiliser une fonction split ici pour construire un tableau d'arguments 
         * split prend e argument une chaine et un dilimiteur pour couper ta chaine dans ce cas 
         * c'est l'espace
         * comme ça argv[0] qui répresente la première case de ton tableau sera la commande 
         * et argv[1] qui représente la deuxième case sera la première optien
         * si tu as besin d'explication just call bissssss 
         */
        if (strcmp(commande, "mkdir") == 0){
            
            mkdir(get_name(commande));
        }
        if (strcmp(commande, "cd") == 0){
            cd(get_name(commande));
        }
        if (strcmp(commande, "pwd") == 0){
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