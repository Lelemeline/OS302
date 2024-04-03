#include "traduction.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


int main(int argc, char *argv[]){

    struct msg_struct msg;
    if(argc != 2){
        printf("Usage : %s \"texte à traduire\"\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    // préparation de la structure
    msg.txt.taille = strlen(argv[1]);
    strcpy(msg.txt.message, argv[1]);
    msg.txt.pid = getpid();
    msg.type = 1;

    int cleEnvoi = ftok("file", 5);
    int cleRecep = ftok("file", 6);
    int idEnvoi = msgget(cleEnvoi, IPC_CREAT);
    int idRecep = msgget(cleRecep, IPC_CREAT);
    if((idRecep == -1) || (idEnvoi == -1)){
        perror("Accès de file de message");
        exit(EXIT_FAILURE);
    }

    //envoi du message à traduire
    if(msgsnd(idEnvoi, &msg, 100, 0) == 0){
		printf("envoi réussi\n");
	}

    while(msgrcv(idRecep, &msg, 100, getpid(), 0) == -1);
    printf("CLIENT: resultat recu depuis le serveur %d : %s\n", msg.txt.pid, msg.txt.message);
    exit(EXIT_SUCCESS);
}