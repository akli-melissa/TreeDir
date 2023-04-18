#ifndef COMMANDES_H
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <ctype.h>

	#define size 1000

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

	//   rep courant

	void init();
	void mkdir(char*); 
	void pwd();
	void cd(char*);

#endif