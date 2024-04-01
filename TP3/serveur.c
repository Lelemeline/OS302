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
    int mode = 0666;
    FILE *fd = NULL;
    if(mkfifo(path, mode) == -1){ // création du tube et gestion de l'erreur
        perror("Erreur lors de la création du tube FIFO");
        exit(EXIT_FAILURE);
    }

    fd = fopen(path, "r");
    if(fd == NULL) { // gestion d'erreur
        perror("Erreur lors de l'ouverture du tube FIFO en mode lecture");
        exit(EXIT_FAILURE);
    }

    char *s = malloc(BUFSIZE * sizeof(char)); // Allocation de mémoire

    while (fgets(s, BUFSIZE, fd) != NULL) { // Lecture depuis le tube FIFO
        printf("%s\n", s);
        memset(s, 0, BUFSIZE); // Réinitialise le tampon
    }

    free(s); // Libération de la mémoire après utilisation
    fclose(fd);
    unlink(path);

    return 0;
}
