#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 50

int main(int argc, char *argv[]){
    FILE *fd = NULL;
    const char *path = "/tmp/fifo";
    if(argc!=2){
        printf("\033[31;01mErreur! Il n'y a que %i argument(s)\033[00m\n",argc);
        return 0;
    }

    if ((fd = fopen(path,"w"))==NULL){
        perror("Erreur lors de l'ouverture du tube");
        exit(EXIT_FAILURE);
    }

    fputs(argv[1],fd);
    fclose(fd);

    return 0 ;
}