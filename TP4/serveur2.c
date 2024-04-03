#include "trad.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>

// Nous rendons ce TP en retard, toutes nos excuses pour cela. Nous sommes restés bloqués sur la gestion de la chaine msg.trad.message. La seule solution trouvée a été d'allouée une taille à cette chaine dans sa définition dans la structure.
// Bien que cette solution ne soit pas parfaite, elle fonctionne. Actuellement, la taille maximum de message est fixée à 100 ( changeable dans le fichier trad.h, #define TAILLE_MAX).

// serveur2 et client2 correspondent au client serveur de l'exercice 2

int main(void)
{
    char *name = "cle";
	struct msg_TRAD_struct msg ;
    int cle_snd = ftok(name, 5);
    int cle_rcv = ftok(name, 6);
    int id_snd = msgget(cle_snd, IPC_CREAT | 0600);
    int id_rcv = msgget(cle_rcv, IPC_CREAT | 0600);
    if((id_snd == -1) || (id_rcv == -1)){ // gestion d'erreur
        perror("Accès de file de message");
        exit(EXIT_FAILURE);
    }

    printf("\033[36;01mSERVEUR : \033[00m Prêt \n");

    while (1==1) // réception et traitement des messages des clients
    {
        if(msgrcv(id_rcv, &msg, sizeof(msg.trad),1, 0) == -1){ // gestion d'erreur
            msgctl(id_rcv, IPC_RMID, NULL);
        }

        else{
            printf("\033[36;01mSERVEUR : \033[00m Réception d'un message de : %d\n", msg.trad.pid);
            msg.type = msg.trad.pid;
            // gestion de fermeture du serveur
            if(strcmp(msg.trad.message, "@")==0){
                msgsnd(id_snd,&msg,sizeof(msg.trad),0);
                exit(EXIT_SUCCESS);
            }
            int i;
            for(i = 0;i<msg.trad.taille;i++){ // traduction du message en caractères majuscules
                msg.trad.message[i] = toupper (msg.trad.message[i]);
            }
            msg.trad.message[i] = '\0';
            msg.trad.pid=getpid();
            if (msgsnd(id_snd, &msg, sizeof(msg.trad), 0)==-1) // gestion d'erreur
            {
                perror("SERVEUR : Echec de l'envoi \n");
            }
            else{ printf("\033[36;01mSERVEUR : \033[00m Envoi au client réussi\n");}
        }

    }
exit(EXIT_SUCCESS);
}
