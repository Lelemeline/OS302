#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// serveur1 et client1 correspondent au client serveur de l'exercice 1

int msg_id;

void raz_msg(int signal) {
	printf("Suppression de la file de message!\n");
	msgctl(msg_id,IPC_RMID,NULL);
}


int main(void)
{
	struct msg_struct msg;
	int i_sig;
	int result;
	char *name = "cle";

	if(msg_id == -1){
		perror("accès à la file\n");
		return EXIT_FAILURE;
	}
	/* liberer la zone de messages sur reception de n'importe quel signal */

	for (i_sig = 0 ; i_sig < NSIG ; i_sig++) {
		if(i_sig != SIGINT)
		signal(i_sig, raz_msg);
	}

	int cle =ftok(name,0);
	msg_id = msgget(cle,IPC_CREAT | 0644);

	printf("SERVEUR: pret!\n");
	while (1 == 1) {
		/* reception */
		if(msgrcv(msg_id, &msg, sizeof(msg.nomee), 1, 0) == -1){
			raz_msg(0);
		}else{
		printf("SERVEUR: réception d'une requete de la part de: %d\n",msg.nomee.pid);
		printf("SERVEUR: opérateur reçu %c \n",msg.nomee.operateur);
		/* preparation de la reponse */

		/* On effectue le calcul */
		if (msg.nomee.operateur=='+'){
			result= msg.nomee.operande1 + msg.nomee.operande2;
			printf("SERVEUR: Le résultat est %d\n",result);
		}
		else if (msg.nomee.operateur=='-'){
			printf("msg op 1 :%d \n",msg.nomee.operande1);
			printf("msg op 2 :%d \n",msg.nomee.operande2);
			result=msg.nomee.operande1 - msg.nomee.operande2;
			printf("SERVEUR: Le résultat est  %d\n",result);
		}
		else if (msg.nomee.operateur=='*'){
			result= msg.nomee.operande1 * msg.nomee.operande2;
			printf("SERVEUR: Le résultat est %d\n",result);
		}
		else if (msg.nomee.operateur=='/'){
			result= msg.nomee.operande1 / msg.nomee.operande2;
			printf("SERVEUR: Le résultat est %d\n",result);
		}
		msg.type=msg.nomee.pid;
		msg.nomee.operande1=result;
		msg.nomee.pid=getpid();

		/* envoi de la reponse */
		if (msgsnd(msg_id, &msg, sizeof(msg.nomee), 0) == 0)
			{
				printf("SERVEUR: Envoi réussi \n");
			}
		}
		printf("==============================================\n");
	}
	return EXIT_SUCCESS;
}
