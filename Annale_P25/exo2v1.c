#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int nbre_sig = 0;

/* Q1
void affichage_pair(int sig){
    nbre_sig++;
    printf("\n");
    if((nbre_sig%2)==0){
        printf("Nombre pair!\n");
    }
}
*/
/* Q2
void affichage_impair(int sig){
    nbre_sig++;
    printf("\n");
    if((nbre_sig%2)==1){
        printf("Nombre impair!\n");
    }
}
*/

/* Ce main comporte des actions de test sur signal pour vérifier que la fonction n'échoue pas
On ne peut dans l'état, n'utiliser que une des deux fonctions à la fois, à savoir compter pair ou impair
int main(void){
    while(1){
        // if(signal(SIGINT,affichage_pair)==SIG_ERR){
        //     perror("Erreur signal");
        // }
        if(signal(SIGINT,affichage_impair)==SIG_ERR){
            perror("Erreur signal");
        }
    }
}
*/
void affichage_pair(int sig){
    nbre_sig++;
    printf("\n");
    if((nbre_sig%2)==0){
        printf("Nombre pair!\n");
        printf("On a reçu %i signaux SIGINT",nbre_sig);
    }
}

int main(void){
    pid_t pid;
    // création et initialisation du tube
    int pipe_fd[2];
    // pipe_fd[0] : lecture seule
    // pipe_fd[1] : écriture seule
    pipe(pipe_fd); // création du tube
    switch(pid=fork()){
        case -1 : // gestion d'erreur
            perror("Erreur de fork\n");
            break;
        case 0 : // cas du fils

            break;
        default:
        // le père va compter les 6 signaux et afficher que il y en a un nombre pair dès que ce sera le cas
            while(nbre_sig!=6){
                if(signal(SIGINT,affichage_pair)==SIG_ERR){
                    perror("Erreur signal");
                }
            }

            break;

    }
}