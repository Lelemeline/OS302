#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


// question 1
/* Crée trois processus fils et place leurs pids dans un tableau dans l'ordre de leur création*/
int creation(pid_t tab[3]) {
    pid_t pid;
    int n = 0; // nombre de fils créés (indice dans le tableau)
    while (n < 3) {
        pid = fork();
        if (pid == -1) {
            perror("Erreur de fork");
            return -1;
        }
        if (pid == 0) {// Processus fils
            exit(0); // Fils termine son exécution
        } else {
            // Processus père met à jour le tableau avec le PID du fils
            tab[n] = pid;
            n++;
        }
    }
    return n; // on renvoie le nombre de fils créés
}


//----------------------------main Q1-------------------------------//
/*
int main(void){
    pid_t tab[3] ;
    int nombre_fils = creation(tab);

    for (int i=0;i<3;i++){
        waitpid(tab[i],NULL,0);
    }
    printf("On a créé %i fils\n",nombre_fils);
    printf("-----------------\n");
     for (int i=0;i<3;i++){
        printf("Element %i : [%d]\n",i,tab[i]);
    }
}
*/

int attente(pid_t tab[3],pid_t fin[3]){
    for(int i = 0;i<3;i++){
        fin[i] = wait(NULL);
    }
    return 0;
}


int main(void){
    pid_t tab[3] ;
    int nombre_fils = creation(tab);
    pid_t fin[3];
    int att = attente(tab,fin);
    if(nombre_fils==-1 || att == -1){
        perror("Problème de pid");
    }
    for (int i=0;i<3;i++){
        printf("Element %i : [%d]\n",i,tab[i]);
    }
    for (int i=0;i<3;i++){
        printf("Fils fini %i : [%d]\n",i,fin[i]);
    }
}

// les fils se terminent dans l'ordre de leur création
/*-------------------Exemple d'exécutiont----------------------
Element 0 : [435808]
Element 1 : [435809]
Element 2 : [435810]
Fils fini 0 : [435808]
Fils fini 1 : [435809]
Fils fini 2 : [435810]
*/
