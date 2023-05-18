#ifndef COMMANDES_H
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <stdbool.h>
	#include <ctype.h>

	#define SIZE 1000
	#define MAX_ARGS 100
	#define RACINE "/"
	#define IS_ABS(path) *path == '/'
	#define IS_REG 1
	#define IS_REP 0
	#define EMPTY(s) *s='\0'
	
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

	void init();
	void mkdir(char*); 
	void pwd();
	void ls();
	int cd(char*);
    char **split(char*, const char) ;
	void free_2d_array(char**);
	void touch(char*);
	void print();
	void freeAll();
	void rm(char*);
	int cp(char*, char*);
	void mv(char*, char*);

#endif