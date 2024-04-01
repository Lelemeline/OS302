#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc,const char *argv[]){

    pid_t pid_fils;

    if(argc!=3){
        printf("\033[31;01mErreur! Il n'y a que %i argument(s)\033[00m\n",argc);
        return 0;
    }

    int pipe_fd[2];
    // pipe_fd[0] : lecture seule
    // pipe_fd[1] : écriture seule
    pipe(pipe_fd); // création du tube

    switch(pid_fils = fork()){
        case -1 : //erreur
            perror("Erreur de fork\n");
            return EXIT_FAILURE ;
        case 0 : //pid_fils;
            close(pipe_fd[0]); // ferme la lecture dans le processus fils
            dup2 (pipe_fd[1], STDOUT_FILENO); //redirige la sortie standard vers le tube
            close(pipe_fd[1]); // ferme l'extrémité d'écriture du tube
            system(argv[1]);
            exit(EXIT_SUCCESS);
        default  : // cas du père
            close(pipe_fd[1]); // ferme l'écriture dans le processus parent
            dup2 (pipe_fd[0], STDIN_FILENO); // redirige l'entrée standard vers le tube
            close(pipe_fd[0]); // ferme l'extrémité de lecture du tube
            system(argv[2]);
            exit(EXIT_SUCCESS);
    }
    wait(NULL);
    exit(EXIT_SUCCESS);
}
