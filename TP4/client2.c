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
        printf("\033[31;01m Usage : %s \"texte à traduire\" \033[00m \n",argv[0]);
        exit(EXIT_FAILURE);
    }

    msg.trad.taille=strlen(argv[1]); // allocation de mémoire dynamique
    strcpy(msg.trad.message,argv[1]);
    msg.trad.pid=getpid();
    msg.type=1;

    // création de clefs d'envoi/ réception nécessaires au bon fonctionnement de msgsnd
    int cle_snd = ftok(name, 5);
    int id_snd = msgget(cle_snd, IPC_CREAT);
    int cle_rcv = ftok(name, 6);
    int id_rcv = msgget(cle_rcv, IPC_CREAT);


    if((id_snd == -1) || (id_rcv == -1)){ // gestion de l'erreur
        perror("Accès de file de message");
        exit(EXIT_FAILURE);
    }

    if (msgsnd(id_snd, &msg, sizeof(msg.trad), 0) == 0) { printf("\033[33;01mCLIENT : \033[00m Envoi réussi de %s \n",msg.trad.message); }
    else {
        perror("echec envoi");
        exit(EXIT_FAILURE);
    }

    while(msgrcv(id_rcv, &msg, sizeof(msg.trad), getpid(), 0) == -1); // attente d'une réponse de la part du serveur.

    printf("\033[33;01mCLIENT : \033[00m resultat recu depuis le serveur %d : %s\n", msg.trad.pid, msg.trad.message); // réponse du serveur et affichage de la chaîne traduite
    exit(EXIT_SUCCESS);
}
