#include "commandes.h"

noeud* REP_COURANT;

static void set_rep(noeud **rep1, noeud **rep2, noeud *rep){
    if (rep2 == NULL){
        *rep1 = rep;
    }else{
        *rep2 = rep;
    }
}

static void pwd_aux(noeud *rep){
    if (rep == NULL || strcmp(rep->nom, RACINE) == 0){
        printf("%s", RACINE);
        return ;
    }
    pwd_aux(rep->pere);
    printf("%s/", rep->nom);
}

static noeud* init_rep(char *nom, liste_noeud* fils, noeud *pere){
    noeud* nouveau = malloc(sizeof(noeud));
    strcpy(nouveau->nom, nom);
    nouveau->est_dossier = true;
    nouveau->pere = pere;
    nouveau->racine = pere->racine;
    nouveau->fils = fils;
    return nouveau;
}

void init(){
	REP_COURANT = malloc(sizeof(noeud));
    REP_COURANT->est_dossier = true;
    strcpy(REP_COURANT->nom, RACINE);
    REP_COURANT->pere = REP_COURANT;
    REP_COURANT->racine = REP_COURANT;
    REP_COURANT->fils = NULL;
}

static noeud* init_fichier(char *nom, noeud *pere){
    noeud* nouveau = malloc(sizeof(noeud));
    strcpy(nouveau->nom, nom);
    nouveau->est_dossier = false;
    nouveau->pere = pere;
    nouveau->racine = pere->racine;
    nouveau->fils = NULL;
    return nouveau; 
}

static int countFils(noeud* rep) {
    int count = 0;
    liste_noeud* fils = rep->fils;
    while (fils != NULL) {
        count++;
        fils = fils->succ;
    }
    return count;
}

static void print_aux(noeud* rep){
    if(rep->est_dossier)
    {
        printf("Noeud: %s (D), Pere: %s, %d fils: \n" , rep->nom, rep->pere->nom, countFils(rep));
        printf("    ");
        liste_noeud* fils = rep->fils;
        while(fils != NULL)
        {
            print_aux(fils->no);
            fils = fils->succ;
        }
    }
    else 
    {
        printf("Noeud: %s (F), Pere: %s \n", rep->nom, rep->pere->nom);
    }
}

static int estParent(noeud *fils, noeud *pere){
    while (pere && pere->pere != pere){
        if (fils == pere){
            printf("Erreur le noeud est parant du repertoire courant\n");
            return 1;
        }
        pere = pere->pere;
    }
    return 0;
}

static void freeAllAux(noeud *racine){
    if (!racine) return;
    liste_noeud *fils = racine->fils, *sauv;
    while (fils){
        freeAllAux(fils->no);
        sauv = fils;
        fils = fils->succ;
        free(sauv);
    }
    free(racine);
}

static char* truncatPath(char *path, char delim){
    char *last = path + strlen(path) - 1;
    while (last != path && *last != delim){
        last--;
    }
    int len = strlen(path) - strlen(last);
    path[len] = '\0';
    return last+1;
}

void mkdir(char *nom){
	if (nom == NULL) return;
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
    liste_noeud* fils = REP_COURANT->fils;
    while (fils != NULL) {
        if (strcmp(fils->no->nom, nom) == 0) {
            printf("Erreur : un dossier portant le même nom existe déjà.\n");
            return;
        }
        fils = fils->succ;
    }
    
    // Création du nouveau noeud dossier
    noeud* nouveau = init_rep(nom, NULL, REP_COURANT);
    
    // Ajout du nouveau noeud dossier à la liste des fils du noeud REP_COURANT
    liste_noeud* nouvel_element = malloc(sizeof(liste_noeud));
    nouvel_element->no = nouveau;
    nouvel_element->succ = REP_COURANT->fils;
    REP_COURANT->fils = nouvel_element;
}

void touch(char *nom)
{
    if (nom == NULL) return;
	// Vérification de la validité du nom
    if (strlen(nom) == 0 || strlen(nom) > 99) {
        printf("Erreur : le nom du fichier doit avoir entre 1 et 99 caractères.\n");
        return;
    }
    for (int i = 0; i < strlen(nom); i++) {
        if (!isalnum(nom[i])) {
            printf("Erreur : le nom du fichier doit contenir seulement des caractères alphanumériques.\n");
            return;
        }   
    }
    // Vérification si un dossier portant le même nom existe déjà
    liste_noeud* fils = REP_COURANT->fils;
    while (fils != NULL) {
        if (strcmp(fils->no->nom, nom) == 0) {
            printf("Erreur : un fichier ou dossier portant le meme nom existe dejà.\n");
            return;
        }
        fils = fils->succ;
    }
    
    // Création du nouveau noeud dossier
    noeud* nouveau = init_fichier(nom, REP_COURANT);
    
    // Ajout du nouveau noeud dossier à la liste des fils du noeud REP_COURANT
    liste_noeud* nouvel_element = malloc(sizeof(liste_noeud));
    nouvel_element->no = nouveau;
    nouvel_element->succ = REP_COURANT->fils;
    REP_COURANT->fils = nouvel_element;
}

char **split(char *str, const char delim) {
   char **result = calloc(sizeof(char*) * MAX_ARGS, MAX_ARGS);
   char *token = strtok(str, &delim);

   int i = 0;

   while (token != NULL) {
      char *p = strchr(token, '\n'); 
      if (p != NULL) *p = '\0';
      result[i] = malloc(strlen(token) + 1);
      strcpy(result[i], token);
      token = strtok(NULL, &delim);
      i++;
   }

   return result;
}

void free_2d_array(char **tab){
    int i = 0;
	while (tab && tab[i] != 0){
		free(tab[i]);
		i++;
	}
    free(tab);
}

int cd(char *chemin, noeud **new_rep){
	if (chemin == NULL){
        set_rep(&REP_COURANT, new_rep, REP_COURANT->racine);
        return 0;
    }
    if (strcmp(chemin, "..") == 0){
        set_rep(&REP_COURANT, new_rep, REP_COURANT->pere);   
        return 0;
    }
	noeud *rep;
	liste_noeud *fils;
	if (chemin && chemin[0] == '/'){
		//chemin abs /dossiers/math/examen/.....
		rep = REP_COURANT->racine;
	}else{
		//chemin relatif math/examen/.....
		rep = REP_COURANT;
	}
	char **dossiers = split(chemin, '/');
	int i=0;
	int exsist;
	while (dossiers && dossiers[i] != 0){
        exsist = 0;
		fils = rep->fils;
		while (fils){
			if (fils->no->est_dossier && strcmp(fils->no->nom, dossiers[i]) == 0){
				rep = fils->no;
				exsist = 1;
				break;
			}
			fils = fils->succ;
		}
		if (exsist == 0){
			printf("Erreur dans le chemin : %s\n", chemin);
			free_2d_array(dossiers);
			return -1;
		}
		i++;
	}
	set_rep(&REP_COURANT, new_rep, rep);
	free_2d_array(dossiers);
    return 0;
}

void pwd(){
	pwd_aux(REP_COURANT);
    printf("\n");
}

void ls(){
    liste_noeud* noeuds = REP_COURANT->fils;
    if (!noeuds) printf("Repertoire vide\n");
    while (noeuds){
        printf("%s\n", noeuds->no->nom);
        noeuds = noeuds->succ;
    }
}

void print(){
    print_aux(REP_COURANT->racine);
    printf("\n");
}

void rm(char *path){
    noeud *rmNode = malloc(sizeof(noeud));
    char *last = truncatPath(path, '/');

    if (cd(path, &rmNode) == -1) return;

    liste_noeud *filsNode = rmNode->fils;
    while (filsNode){
        if (strcmp(filsNode->no->nom, last) == 0){
            rmNode = filsNode->no;
            break;
        }
        filsNode = filsNode->succ;
    }

    if (!filsNode){
        printf("Erreur dans le chemin\n");
        return;
    }

    if (IS_ABS(path) && estParent(rmNode, REP_COURANT)) return;

    liste_noeud *fils = rmNode->pere->fils, *sauv = fils;
    while(fils){
        if(fils->no == rmNode){
            if (sauv == fils) rmNode->pere->fils = sauv->succ;
            sauv->succ = fils->succ;
            break;
        }
        sauv = fils;
        fils = fils->succ;
    }
    free(last);
    freeAllAux(rmNode);
}

void freeAll(){
    freeAllAux(REP_COURANT->racine);
}