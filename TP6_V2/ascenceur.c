#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <err.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>


void safeKill(int sem_id){
    semctl(sem_id, 0, IPC_RMID);

    exit(0);
}

int main (int argc, char *argv[]){
    // gestion d'erreur
    if(argc!=2){
        perror("Nombre d'arguments incorrect");
    }
    int n = atoi(argv[1]); // nombre d'ouvriers
    int max = n;
    pid_t pid = 2;

    // création et initialisation du sémaphore
    char *nom_clef = "clef";
    key_t clef = ftok(nom_clef,2);
    if(clef <0) perror("Erreur de clef");
    int sem_id;
    if((sem_id = semget(clef,1,IPC_CREAT| 0400 | 0200))==-1){
        perror("Erreur semget");
        safeKill(sem_id);
    }
    struct sembuf buf ;
    buf.sem_num = 0;
    buf.sem_op = -1;
    buf.sem_flg = SEM_UNDO;
    if(semctl(sem_id,0,SETVAL,2)==-1){
        perror("Erreur SETVAL");
        safeKill(sem_id);

    }

    // création du segment de mémoire partagée
    int shm_id;
    if((shm_id = shmget(clef,2*sizeof(pid_t),IPC_CREAT| 0400 | 0200))==-1){
        perror("Erreur création de segment");
        safeKill(sem_id);
    }

    void *adresse_segment = shmat(shm_id,NULL,SHM_RND); // attachement du segment
    pid_t* pointeur =  (pid_t*) adresse_segment;
    pointeur[0] = 0;
    pointeur[1] = 0;


    // création des n fils
    while((pid = fork())!=0 && n>0){
        if(pid==-1) {
            perror("Erreur de fork");
            safeKill(sem_id);}
        n-=1;
    }


    if(pid == 0){ // code fils
        if(semop(sem_id,&buf,1)==-1){
            perror ("Erreur opération de sémaphore");
            return 0;
        }
        if(pointeur[0]!=0){
            pointeur[1] = getpid();
            printf("Je viens de monter dans l'ascenseur [%d]\n", getpid());
        }
        else {
            pointeur[0] = getpid();
            printf("Je viens de monter dans l'ascenseur [%d]\n", getpid());
        }


        pause();
        return 0;
    }
    // code père
    while(n<max){
        if(semctl(sem_id,0,GETVAL)==0){
            sleep(1);

            printf("Les ouvriers %i et %i sont en haut\n",pointeur[0],pointeur[1]);

            kill(pointeur[0],SIGUSR1);
            kill(pointeur[1],SIGUSR1);
            pointeur[0] = 0;
            pointeur[1] = 0;

            printf("Ascenseur libre\n");
            n+=2;
            if((max%2==1) && (n==max-1)){
                semctl(sem_id,0,SETVAL,1);
                printf("prêt à prendre le dernier ouvrier\n");
            }
        }
    }
    printf("Tous les ouvriers sont au travail, on peut fermer l'ascenceur\n");
    safeKill(sem_id);
    shmdt(adresse_segment);
}