#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msg_id;

void raz_msg(int signal) {
	//printf("Suppression de la file de message!\n");
	msgctl(msg_id, IPC_RMID, NULL);
}



int main(int argc, char const *argv[])
{
	struct msg_struct msg;
	int i_sig;
	int result;

	/* liberer la zone de messages sur reception de n'importe quel signal */

	for (i_sig = 0 ; i_sig < NSIG ; i_sig++) {
		if(i_sig != SIGINT)
		signal(i_sig, raz_msg);
	}
	int cle = ftok("file", 5);
	msg_id = msgget(cle, IPC_CREAT | 0600);
	if(msg_id == -1){
		perror("erreur création de file");
		return EXIT_FAILURE;
	}
	printf("SERVEUR: pret!\n");
	while (1 == 1) {
		/* reception */
		if(msgrcv(msg_id, &msg, 50, 1, 0) == -1){
			raz_msg(0);
		}else{
			printf("SERVEUR: reception d'une requete de la part de: %d\n",msg.message.pid);
			/* preparation de la reponse */
			msg.type = msg.message.pid;
			msg.message.pid = getpid();
			switch(msg.message.operation){
				case '+':
					result = msg.message.operande1 + msg.message.operande2;
					break;
				case '-':
					result = msg.message.operande1 - msg.message.operande2;
					break;
				case 'x':
					result = msg.message.operande1 * msg.message.operande2;
					break;
				case '/':
					result = (msg.message.operande1) / (msg.message.operande2);
					break;
			}
			msg.message.operande1 = result;
			/* A COMPLETER */
			/* envoi de la reponse */
			msgsnd(msg_id, &msg, 50, 0);
		}
	}
	return EXIT_SUCCESS;
}

