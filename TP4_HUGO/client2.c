#include "trad.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>


int main(int argc, char *argv[]){
    char *name = "cle";
    struct msg_TRAD_struct msg; // création structure msg

    if(argc != 2){ // gestion d'erreur
        printf("Usage : %s \"texte à traduire\"\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    msg.trad.taille=strlen(argv[1]); // allocation de mémoire dynamique
    strcpy(msg.trad.message,argv[1]);
    msg.trad.pid=getpid();
    msg.type=1;


    int cle_snd = ftok(name, 5);
    int id_snd = msgget(cle_snd, IPC_CREAT);
    printf("id_snd :%d \n",id_snd);


    int cle_rcv = ftok(name, 6);
    int id_rcv = msgget(cle_rcv, IPC_CREAT);
    printf("id_rcv :%d \n",id_rcv);


    if((id_snd == -1) || (id_rcv == -1)){
        perror("Accès de file de message");
        exit(EXIT_FAILURE);
    }

    if (msgsnd(id_snd, &msg, sizeof(msg.trad), 0) == 0)
	{
		printf("CLIENT: Envoi réussi de %s \n",msg.trad.message);
	}
    else
    {
        printf("echec de l'envoi\n");

    }


    while(msgrcv(id_rcv, &msg, sizeof(msg.trad), getpid(), 0) == -1);
    printf("CLIENT: resultat recu depuis le serveur %d : %s\n", msg.trad.pid, msg.trad.message);
    exit(EXIT_SUCCESS);
}
