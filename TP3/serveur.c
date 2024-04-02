#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFSIZE 50

int main(void){
    const char *path = "/tmp/fifo";
    int mode = 0666; // droits d'accès en lecture et écriture
    FILE *fd = NULL;
    if(mkfifo(path, mode) == -1){ // création du tube et gestion de l'erreur
        perror("Erreur lors de la création du tube FIFO");
        exit(EXIT_FAILURE);
    }
    int i = 0 ;
    char *s = malloc(BUFSIZE * sizeof(char)); // Allocation de mémoire
    printf("\033[32;01m==========================Ouverture du serveur=================================\033[00m\n");

    while(1){
        fd = fopen(path, "r"); // ouverture dans chaque boucle du fichier, car fermé à chaque fin d'exécution du client

        if(fd == NULL) { // gestion d'erreur
            perror("Erreur lors de l'ouverture du tube FIFO en mode lecture");
            exit(EXIT_FAILURE);
        }

        while (fgets(s, BUFSIZE, fd) != NULL) { // Lecture depuis le tube FIFO
            if(strcmp(s,"quit")==0){ // condition pour fermer le serveur
                printf("\033[31;01m==========================Fermeture du serveur=================================\033[00m\n");
                free(s); // Libération de la mémoire après utilisation
                fclose(fd);
                unlink(path); // supprimer le fichier
                return 0;
            }
            printf("%s\n", s); // sinon, affichage du message client
            memset(s, 0, BUFSIZE); // Réinitialise le tampon
        }
    }

}
