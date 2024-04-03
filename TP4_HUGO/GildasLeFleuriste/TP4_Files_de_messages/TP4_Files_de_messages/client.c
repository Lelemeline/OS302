#include "calcul.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>


int main(int argc, char const *argv[])
{
	int msg_id;
	struct msg_struct msg;

	if (argc != 4) {
		printf("Usage: %s operande1 {+|-|x|/} operande2\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* il faut eviter la division par zero */
	if((argv[2][0] == '/') && (argv[3][0] == '0')){
		printf("division par 0\n");
		return EXIT_FAILURE;
	}
	/* ATTENTION : la file de messages doit avoir ete creee par le serveur. Il
	 * faudrait tester la valeur de retour (msg_id) pour verifier que cette
	 * creation a bien eu lieu. */
	int cle = ftok("file", 5);
	msg_id = msgget(cle,IPC_CREAT);
	if(msg_id == -1){
		perror("accès à la file\n");
		return EXIT_FAILURE;
	}
	printf("CLIENT %d: preparation du message contenant l'operation suivante:%d %c %d\n", getpid(), atoi(argv[1]), argv[2][0], atoi(argv[3]));

	/* On prepare un message de type 1 à envoyer au serveur avec les
	 * informations necessaires */
	msg.type = 1;
	msg.message.pid = getpid();
	msg.message.operation = argv[2][0];
	msg.message.operande1 = atoi(argv[1]);
	msg.message.operande2 = atoi(argv[3]);
	/* envoi du message */

	if(msgsnd(msg_id, &msg, 50, 0) == 0){
		printf("envoi réussi\n");
	}
	/* reception de la reponse */
	while(msgrcv(msg_id, &msg, 50, getpid(), 0) == -1);
	printf("CLIENT: resultat recu depuis le serveur %d : %d\n", msg.message.pid, msg.message.operande1);
	return EXIT_SUCCESS;
}
