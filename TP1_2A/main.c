#include "includes/main.h"


int main() {
    char input[128];
    

    // Affichage du message d'accueil et premier prompt
    afficherMessageAccueil();
    printf("enseash %% ");
    fflush(stdout);

    while (1) {
        // Détection d'une commande de sortie
        if (detecterCtrlD(input)) break;
        if (verifierExit(input)) break;

        supprimerRetourLigne(input);

        // Ignorer les entrées vides
        if (strlen(input) == 0) {
            printf("enseash %% ");
            fflush(stdout);
            continue;
        }

        creerProcessusFils(input);
    }
    return 0;
}

// Fonction pour afficher le message d'accueil
void afficherMessageAccueil() {
    printf("Bienvenue dans le Shell ENSEA.\n");
    printf("Pour quitter, tapez 'exit' ou <Ctrl>+D.\n");
}

// Fonction pour détecter <Ctrl>+D
int detecterCtrlD(char *input) {
    if (fgets(input, 128, stdin) == NULL) {
        printf("%s", Exit_message);
        return 1;
    }
    return 0;
}

// Fonction pour vérifier si la commande est 'exit'
int verifierExit(char *input) {
    if (strcmp(input, "exit\n") == 0 || strcmp(input, "exit") == 0) {
        printf("%s", Exit_message);
        return 1;
    }
    return 0;
}

// Fonction pour supprimer le retour à la ligne de l'entrée utilisateur
void supprimerRetourLigne(char *input) {
    input[strcspn(input, "\n")] = '\0';
}

// Fonction pour découper une commande en arguments
void decouperCommande(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Terminer le tableau par NULL pour `execvp`
}

// Fonction pour les redirections d'un fichier
void Redirections(char *input, char **command, char **inputFile, char **outputFile) {
    *inputFile = NULL;
    *outputFile = NULL;

    char *inputRedirect = strstr(input, "<");
    char *outputRedirect = strstr(input, ">");

    if (inputRedirect) {
        *inputRedirect = '\0'; // Terminer la commande ici
        inputRedirect++;
        *inputFile = strtok(inputRedirect, " "); // Récupérer le fichier d'entrée
    }

    if (outputRedirect) {
        *outputRedirect = '\0'; // Terminer la commande ici
        outputRedirect++;
        *outputFile = strtok(outputRedirect, " "); // Récupérer le fichier de sortie
    }

    // La commande restante après avoir extrait les redirections
    *command = strtok(input, " ");
}


// Fonction pour gérer la redirection d'entrée
void RedirectionEntree(char *inputFile) {
    int fd = open(inputFile, O_RDONLY);
    if (fd < 0) {
        perror(Erreur_message);
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror(Erreur_message);
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Fonction pour gérer la redirection de sortie
void RedirectionSortie(char *outputFile) {
    int fd = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror(Erreur_message);
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror(Erreur_message);
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Fonction pour créer et gérer un processus fils
int creerProcessusFils(char *input) {
    pid_t pid;
    int status;
    struct timespec start, end;
    char buffer[256];

    char *args[128];
    char *command, *inputFile, *outputFile;

    // Analyse de la commande et des redirections
    Redirections(input, &command, &inputFile, &outputFile);

    decouperCommande(command, args);

    // Début de la mesure du temps
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror(Erreur_message);
        return -1;
    }

    pid = fork();

    if (pid < 0) {
        perror(Erreur_message);
        return -1;
    }

    if (pid == 0) { // Processus fils
         
         // Gestion des redirections d'entrée
        if (inputFile) {
            RedirectionEntree(inputFile);
        }

        // Gestion des redirections de sortie
        if (outputFile) {
            RedirectionSortie(outputFile);
        }

        // Exécuter la commande
        execvp(args[0], args);
        perror(Unknow_message); 
        exit(EXIT_FAILURE);
    
    } 
    
    else { // Processus parent
        waitpid(pid, &status, 0);

        // Fin de la mesure du temps
        if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
            perror(Erreur_message);
            return -1;
        }

        // Calcul du temps en millisecondes
        long duration = (end.tv_sec - start.tv_sec) * 1000 +
                        (end.tv_nsec - start.tv_nsec) / 1000000;

        // Affichage prompt selon les cas
        if (WIFEXITED(status)) {
            int exitCode = WEXITSTATUS(status);
            sprintf(buffer, "enseash [exit:%d|%ld ms] %% ", exitCode, duration);
        } else if (WIFSIGNALED(status)) {
            int signal = WTERMSIG(status);
            sprintf(buffer, "enseash [sign:%d|%ld ms] %% ", signal, duration);
        }

        // Assure que le prompt est visible
        fputs(buffer, stdout);
        fflush(stdout);
    }
    return 0;
}

