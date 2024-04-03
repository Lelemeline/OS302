#include "traduction.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


int main(){
    struct msg_struct msg;

    int cleRecep = ftok("file", 5);
    int cleEnvoi = ftok("file", 6);
    int idRecep = msgget(cleRecep, IPC_CREAT | 0600);
    int idEnvoi = msgget(cleEnvoi, IPC_CREAT | 0600);
    if((idRecep == -1) || (idEnvoi == -1)){
        perror("Création de file de message");
        exit(EXIT_FAILURE);
    }
    printf("SERVEUR: pret!\n");
    while(1){
        if(msgrcv(idRecep,&msg,100,1,0) == -1){
            msgctl(idRecep, IPC_RMID, NULL);
        }else{
            printf("SERVEUR : Réception d'un message de : %d\n", msg.txt.pid);
            msg.type = msg.txt.pid;
            if(!strcmp(msg.txt.message, "@")){
                msgsnd(idEnvoi,&msg,100,0);
                exit(EXIT_SUCCESS);
            }
            for(int i=0;i<msg.txt.taille;i++){
                // si le caractère est en minuscule -> Majuscule
                if((msg.txt.message[i]>=97) && (msg.txt.message[i]<=122)){ 
                    msg.txt.message[i] -= 32;
                }
            }
            msg.txt.pid = getpid();
            if(msgsnd(idEnvoi,&msg,100,0) == -1){
                printf("échec de l'envoi\n");
            }
        }
    }
    exit(EXIT_SUCCESS);
}