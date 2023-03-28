#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Définition de la structure 
struct noeud;
struct liste_noeud;
struct noeud {
    bool est_dossier;
    char nom[100];
    struct noeud* pere;
    struct noeud* racine;
    struct liste_noeud* fils;
};
struct liste_noeud {
    struct noeud* no;
    struct liste_noeud* succ;
};
typedef struct noeud noeud;
typedef struct liste_noeud liste_noeud;



// Déclaration de la fonction mkdir
void mkdir(noeud* courant, char* nom) {
    // Vérification de la validité du nom
    if (strlen(nom) == 0 || strlen(nom) > 99) {
        printf("Erreur : le nom du dossier doit avoir entre 1 et 99 caractères.\n");
        return;
    }
    for (int i = 0; i < strlen(nom); i++) {
        if (!isalnum(nom[i])) {
            printf("Erreur : le nom du dossier doit contenir seulement des caractères alphanumériques.\n");
            return;
        }   
    }
    
    // Vérification si un dossier portant le même nom existe déjà
    liste_noeud* fils = courant->fils;
    while (fils != NULL) {
        if (fils->no->est_dossier && strcmp(fils->no->nom, nom) == 0) { //faut il verifier si c'est un dossier ou pas ? esk un fichier et un dossier peuvent avoir le meme nom ? 
            printf("Erreur : un dossier portant le même nom existe déjà.\n");
            return;
        }
        fils = fils->succ;
    }
    
    // Création du nouveau noeud dossier
    noeud* nouveau = malloc(sizeof(noeud));
    nouveau->est_dossier = true;
    strcpy(nouveau->nom, nom);
    nouveau->pere = courant;
    nouveau->racine = courant->racine;
    nouveau->fils = NULL;
    
    // Ajout du nouveau noeud dossier à la liste des fils du noeud courant
    liste_noeud* nouvel_element = malloc(sizeof(liste_noeud));
    nouvel_element->no = nouveau;
    nouvel_element->succ = NULL;
    if (courant->fils == NULL) {
        courant->fils = nouvel_element;
    }
    else {
        liste_noeud* dernier = courant->fils;
        while (dernier->succ != NULL) {
            dernier = dernier->succ;
        } 
        dernier->succ = nouvel_element;
    }
}

