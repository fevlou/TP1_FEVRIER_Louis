#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h> 
#include <time.h>
#include <errno.h>
#include <fcntl.h> // Pour ouvrir un fichier

const char Exit_message[] = "BYE BYE\n";
char Erreur_message[] = "Error Process\n";
char Unknow_message[] = "Command unknow\n";


// Prototypes des fonctions
void afficherMessageAccueil();
int detecterCtrlD(char *input);
int verifierExit(char *input);
void supprimerRetourLigne(char *input);
int creerProcessusFils(char *input);
void decouperCommande(char *input, char **args);
void Redirections(char *input, char **command, char **inputFile, char **outputFile);
void RedirectionEntree(char *inputFile);
void RedirectionSortie(char *outputFile);
