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

int main(void)
{
    char *name = "cle";
	struct msg_TRAD_struct msg ;
    int cle_snd = ftok(name, 5);
    int cle_rcv = ftok(name, 6);
    int id_snd = msgget(cle_snd, IPC_CREAT | 0600);
    int id_rcv = msgget(cle_rcv, IPC_CREAT | 0600);
    printf("id_snd :%d \n",id_snd);
    printf("id_rcv :%d \n",id_rcv);

    if((id_snd == -1) || (id_rcv == -1)){
        perror("Accès de file de message");
        exit(EXIT_FAILURE);
    }

    printf("SERVEUR: Prêt \n");

    while (1==1)
    {
        //msg.trad.message = malloc((msg.trad.taille) * sizeof(char));
        if(msgrcv(id_rcv, &msg, sizeof(msg.trad),1, 0) == -1){
            msgctl(id_rcv, IPC_RMID, NULL);
        }

        else{
            printf("chaine : %s\n",msg.trad.message);
            printf("SERVEUR : Réception d'un message de : %d\n", msg.trad.pid);
            // if (msg.trad.message == NULL) {
            //     perror("Allocation de mémoire échouée");
            //     exit(EXIT_FAILURE);
            // }
            msg.type = msg.trad.pid;
            if(strcmp(msg.trad.message, "@")==0){
                msgsnd(id_snd,&msg,sizeof(msg.trad),0);
                exit(EXIT_SUCCESS);
            }
            printf("structure : pid = %i, taille = %i, message = %s\n",msg.trad.pid,msg.trad.taille,msg.trad.message);
            int i;
            for(i = 0;i<msg.trad.taille;i++){
                msg.trad.message[i] = toupper (msg.trad.message[i]);
            }
            msg.trad.message[i] = '\0';
            printf("message traduit == %s\n",msg.trad.message);
            msg.trad.pid=getpid();
            if (msgsnd(id_snd, &msg, sizeof(msg.trad), 0)==-1)
            {
                perror("SERVEUR : Echec de l'envoi \n");
            }
        }

    }
exit(EXIT_SUCCESS);
}
