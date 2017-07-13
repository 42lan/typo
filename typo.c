#include "typo.h"

/* Fonction qui gère les erreur en affichant le message correspondant au code
 * passé en paramètre
 */
void error(CodeErreur code){
	switch(code){
		case NO_ARGS : fprintf(stderr,"Au mois un argumets est requise!\n"); break;
		case ERR_OPEN : fprintf(stderr,"Impossible d'ouvrire le fichier!\n"); break;
		case ALLOC_TAB : fprintf(stderr,"Erreur d'allocation de mémoire niveau 1!\n"); break;
		case ALLOC_TABn2 : fprintf(stderr,"Erreur d'allocation de mémoire niveau 2!\n"); break;
		default: fprintf(stderr,"Code erreur inconnu!\n");
	}
	exit(code);
}



/* La fonction essaye d'ouvrire le fichier. Elle renvoye le poiteur si elle
 * reussi, si non appele a la fonction erreur() avec le code 2 qui correspond
 * à l'échec de l'ouverture
 */
FILE* ouvrireFichier(char* fichier){
	FILE *pFile=NULL; /* Déclaration de la variable-poiteur pFile de type FILE initialisé à NULL */
	
	pFile=fopen(fichier, "r");	/* Ouverture du fichier en mode lecteur seule */
	if(pFile == NULL)	/* Si la variable pFile poité vers NULL appelé la fonction error() */
   	error(2);	/* ERR_OPEN */	
	return pFile;
}



/* La fonction compte le nombre de mots dans le flux passé en paramètre
 * curseur - indicateur de position
 */
int compteMots(FILE* pFile){
	char mot[TAILLE_MAX];	/* Déclaration d'un tableau de taille TAILLE_MAX. Si TAILLE_MAX=3, mot=[][][] */
	int nbMots=0;	/* Déclaration de la variable pour stocké le nombre de mots */
	
	while(fscanf(pFile, "%s", mot) != EOF) /* Tant que fscanf() lit depuis flux poité par pFile une chaine "%s" en la mettant dans mot ne rencontre pas le EOF */
		nbMots++;	/* Incremente la variable quand fscanf() lit une chaine */
	rewind(pFile);	/* rewind() remet le curseur du flux poité par pFile en debut  /!\ Si je ne fais pas, le curseur reste sur EOF */
	return nbMots; /* Retourne le nombre de mots compté dans le flux poité par pFile */
}



/* La fonction alloue dynamiquement le tableau de tableau en fonction du nombre 
 * de mots passe en paramètre et les remplit avec le flux poité par pFile 
 */
char** initTableauMots(FILE* pFile, int nbMots){
	char** mots=NULL;	/* Déclaration d'un tableau de tableau en initialisant à NULL*/
	int i, j; /* Déclaration des variables pour l'incrementation */
	
	mots=malloc(sizeof(char*) * nbMots);	/* Allocation dynamique de la mémoire d'un tableau de nbMots fois de la taille d'un char* */
	if(mots == NULL)	/* Si après l'allocation mots poite vers NULL appelé la fonction exit() avec code 2 */
		error(2);	/* ALLOC_TAB */
		
	for(i=0; i<nbMots; i++){	/* Parcour de tableau nbMots fois pour l'allocation d'espace mémoire */
		mots[i]=malloc(sizeof(char) * 20);	/* Allocation dynamique d'espace mémoire des nbMots mots, 20 fois de la taille d'un char */
		if(mots[i]==NULL){	/* Si l'allocation de l'espace mémoire échoue */
			for(j=0; j<nbMots+1; j++)	/* Parcour de tableau dans le tableau afin de libérer l'espace mémore jusqu'a nbMots+1 ('\n' inclus) */
				free(mots[i]);	/* Liber espace mémore poité par mots[i] */
			free(mots);	/* Liber espace mémore crée pour le tableau mots */
			error(3);	/* ALLOC_TABn2 */
		}
		fscanf(pFile, "%s", mots[i]);	/* Inserer une chaine de caractère "%s" lut à partir de pFile dans l'adresse poité par mots[i] */
	}
	return mots;	/* Retourner le tableau de tableau constitué */
}



/* Cette fonction, comme son nom indique, permet a l'utilisateur de joue. Elle affichie un mot
 * et demande a l'utilisateur la saissie. Puis compare ce que est affiché avec ce qui est saissie.
 * Increment le счётчик de fautes. A la fin de joue afficher le message avec les fautes et le temps
 * pendant lequel l'utilisateur a joue.
 */
void joue(char** mots, int nbMots){
	char motSaissi[TAILLE_MAX]="";
	int i, nbFautes=0;
	time_t start_t, end_t;
	
	for(i=0; i<nbMots; i++){
		start_t=time(&start_t);
		printf("mot[%d] = %s\n", i, mots[i]);

		do{
			printf(">");
			scanf("%s", motSaissi);
			if(strcmp(motSaissi, mots[i]) != 0)
				nbFautes++;
		}while(strcmp(motSaissi, mots[i]));
		
		
	}
	end_t=time(&end_t);
	printf("Vous avez écrit %d mot(s) en %.1f sec. Le nombre de fautes est: %d\n", nbMots, difftime(end_t, start_t), nbFautes);
}


/* Cette fonction effectue la vérification sur le deuxième argument
 */
int verifArgs(int argc, int nbMots, char* argv2){
	int nbMotsJoue=0;
	
	if(argc==2){ /* Si le troisieme argument n'est pas presisé on joue sur la totalité */
		nbMotsJoue=nbMots;
		printf("On vas joue sur %d mots\n", nbMotsJoue);
	}
	if((argc==3) || (argc>3)){ /* Si le troisieme argument est presisé, on joue sur ce nombre de mots */
		nbMotsJoue=atoi(argv2);
		printf("Tu as choisis de joue sur %d mots\n", nbMotsJoue);
	}
	if(atoi(argv2) > nbMots){
	
	}
	return nbMotsJoue;
}
