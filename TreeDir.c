#include "commandes.h"

char *get_arg(char *chaine){
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
    while (nom && *nom != ' '){
        nom++;
    }
    char *result = malloc(size);
    strncpy(result, sauv, nom-sauv-1);
    return result;
}

//mkdir aaaaa

int main(){
    char *arg = malloc(size);
    init();
    while (1){
        printf("> ");
        gets(arg);
        char *commande = get_commande(arg);
        printf("%s\n", commande);
        if (strcmp(commande, "mkdir") == 0){
                mkdir(get_arg(commande));
        }else if (strcmp(commande, "cd") == 0){
            cd(get_arg(commande));
        }else if (strcmp(commande, "pwd") == 0){
            pwd();
        }
        else{
            printf("Erreur dans la commande\n");
        }
    }
    exit(0);
}