#include "commandes.h"
noeud* REP_COURANT;



noeud* init_rep(char *nom, liste_noeud* fils, noeud *pere){
	noeud* nouveau = malloc(sizeof(noeud));
	nouveau->est_dossier = true;
	strcpy(nouveau->nom, nom);
	if (pere == NULL){
		nouveau->pere = nouveau;
		nouveau->racine = nouveau;
	}
	else{
		nouveau->pere = pere;
		nouveau->racine = pere->racine;
	}
	nouveau->fils = fils;
	return nouveau;
}
void init(){
	REP_COURANT = NULL;
}
void mkdir(char *nom){
	printf("hfsfbdf\n");
	if (nom == NULL) return;
	printf("jjjj\n");
	// Vérification de la validité du nom
    if (strlen(nom) == 0 || strlen(nom) > 99) {
        printf("Erreur : le nom du dossier doit avoir entre 1 et 99 caractères.\n");
        return;
    }
	printf("mmmmm\n");
    for (int i = 0; i < strlen(nom); i++) {
        if (!isalnum(nom[i])) {
            printf("Erreur : le nom du dossier doit contenir seulement des caractères alphanumériques.\n");
            return;
        }   
    }
    printf("hello\n");
    if (REP_COURANT == NULL){
    	REP_COURANT = init_rep("/", NULL, NULL);
    	return;
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
    nouvel_element->succ = NULL;
    if (REP_COURANT->fils == NULL) {
        REP_COURANT->fils = nouvel_element;
    }
    else {
        liste_noeud* dernier = REP_COURANT->fils;
        while (dernier->succ != NULL) {
            dernier = dernier->succ;
        } 
        dernier->succ = nouvel_element;
    }
}

char **split(char *str, const char delim) {
   char **result = NULL;
   char *token = strtok(str, &delim);

   int i = 0;

   while (token != NULL) {
      result = realloc(result, sizeof(char*) * (i + 1));
      result[i++] = strdup(token);
      token = strtok(NULL, &delim);
   }

   return result;
}

void free_2d_array(char **tab){
	while (tab){
		free(*tab);
		tab++;
	}
	free(tab);
}

void cd(char *chemin){
	if (chemin == NULL) return;
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
	int exsist = 0;
	while (dossiers){
		fils = rep->fils;
		while (fils){
			if (fils->no->est_dossier && strcmp(fils->no->nom, *(dossiers+i))){
				rep = fils->no;
				exsist = 1;
				break;
			}
			fils = fils->succ;
		}
		if (exsist == 0){
			printf("Erreur dans le chemin : %s\n", chemin);
			free_2d_array(dossiers);
			return;
		}
		dossiers++;
	}
	REP_COURANT = rep;
	free_2d_array(dossiers);
}

void pwd_aux(noeud *rep){

	if ( rep ==NULL || strcmp(rep->nom, "") == 0) return ;
	pwd_aux(rep->pere);
	printf("/%s", rep->nom);
}

void pwd(){
	
	pwd_aux(REP_COURANT);
}