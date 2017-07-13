#ifndef __TYPO__
#define __TYPO__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE_MAX 100


typedef enum {false=0, true=1}Boolean;	/* Le type boolean n'existe pas en C, donc on crée */
typedef enum {NO_ARGS=1, ERR_OPEN=2, ALLOC_TAB=3, ALLOC_TABn2=4}CodeErreur;	/* Enumeration contenant les codes d'erreurs */

void error(CodeErreur code);
FILE* ouvrireFichier();
int compteMots(FILE* pFile);
char** initTableauMots(FILE* pFile, int nbMots);
void joue(char** mots, int nbMots);
int verifArgs(int argc, int nbMots, char* argv2);

#endif
