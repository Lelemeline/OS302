#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>

int cree_segment(int taille, char* nom, int cle) {
    key_t mem_clef;
    if ((mem_clef = ftok(nom,cle)) == -1) {
        perror("Erreur de création de clé");
        exit(EXIT_FAILURE);
    }
    int segment;
    if ((segment = shmget(mem_clef, taille, IPC_CREAT | 0644)) == -1) {
        perror("Erreur de création de segment");
        return -1;
    }
    return segment;
}

int main(int argc, char *argv[]) {
    // Définition des variables
    int pid1, pid2;     // PIDs des processus fils
    char *mem1 = malloc(5*sizeof(int));
    char *mem2 = malloc(5*sizeof(int));
    // Pointeurs vers les segments mémoire
    int shmid1, shmid2; // Identificateurs des segments mémoire
    char nom[12] = "ascenceur.c";
    int cle = 2; // Clés pour la création des segments de mémoire
    int status;

    //gestion de l'erreur usage
    if (argc != 2) {
        perror("Usage : ./exo2 <nombre d'ouvriers>");
        exit(EXIT_FAILURE);
    }

    int nombre_ouvriers = atoi(argv[1]);

    //création d'un sémaphore
    int sem_id= semget(ftok(nom,cle),1,IPC_CREAT|0600);
    semctl(sem_id,1,SETVAL,0);

    // Création des segments de mémoire partagée pour chaque fils
    if ((shmid1 = cree_segment(100, nom, cle)) == -1 || (shmid2 = cree_segment(100, nom, cle)) == -1) {
        perror("Création du segment mémoire");
        exit(EXIT_FAILURE);
    }
    while(nombre_ouvriers>0){
    // Création du premier fils
    switch (pid1 = fork()) {
        case -1:
            perror("Impossible de créer un processus fils!");
            exit(-1);
            break;
        case 0: // Fils 1
            // Attachement au segment mémoire
            mem1 = shmat(shmid1, NULL, 0);
            // Écriture du PID du fils dans le segment mémoire
            pid_t fils1 = getpid();
            sprintf(mem1, "%d", fils1);
            // Détachement du segment mémoire
            shmdt(mem1);
            semctl(sem_id,1,SETVAL,1);
            exit(EXIT_SUCCESS);
            break;
        default: // Père
            break;
    }

    // Création du deuxième fils
    switch (pid2 = fork()) {
        case -1:
            perror("Impossible de créer un processus fils!");
            exit(-1);
            break;
        case 0: // Fils 2
            // Attachement au segment mémoire
            mem2 = shmat(shmid2, NULL, 0);
            // Écriture du PID du fils dans le segment mémoire
            pid_t fils2 = getpid();
            sprintf(mem2, "%d", fils2);
            // Détachement du segment mémoire
            shmdt(mem2);
            semctl(sem_id,1,SETVAL,2);
            exit(EXIT_SUCCESS);
            break;
        default: // Père
            break;
    }
    // comportement du père
    // Attente de la fin de l'exécution des fils
    waitpid(pid1, &status, WUNTRACED);
    waitpid(pid2, &status, WUNTRACED);

    mem1 = shmat(shmid1,NULL,0); // attache au segment mémoire
    mem2 = shmat(shmid2,NULL,0); // attache au segment mémoire
    struct sembuf asc = {sem_id,1,0}; //strucutre sem_oper de l'ascenceur
    //printf("Montée dans l'ascenceur de deux fils de pid %s et %s\n", mem1,mem2);
    if(semctl(sem_id,1,GETVAL)==2){
        printf("Les deux ouvriers de pid %s et %s sont montés\n",mem1,mem2);
        semctl(sem_id,1,SETVAL,0);
        // Suppression des segments de mémoire partagée
        shmctl(shmid1, IPC_RMID, 0);
        shmctl(shmid2, IPC_RMID, 0);
        nombre_ouvriers -=2;
    }
    }

    return 0;
}
