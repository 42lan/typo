#include "typo.h"

int main(int argc, char* argv[]){
	int nbMots=0, nbMotsJoue=0;
	FILE* pFile=NULL;
	char** mots=NULL;
	/* int i; for(i=0; i<argc; i++) printf("argv %d = %s\n", i, argv[i]); */
	printf("%d\n", argc);
	if(argc<2) error(1);
	
	pFile=ouvrireFichier(argv[1]);
	nbMots=compteMots(pFile);
	printf("---Le nombre de mots dans le fichier: %d---\n", nbMots);
	
	mots=initTableauMots(pFile, nbMots);
	
	nbMotsJoue=verifArgs(argc, nbMots, argv[2]);

	joue(mots, nbMotsJoue);

	return 0;
}
