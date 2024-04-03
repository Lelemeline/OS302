#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "calcul.h"


int main(int argc, char const *argv[])
{
	int msg_id,resultat;
	char *name = "cle";
	struct msg_struct msg;

	if (argc != 4) {
		printf("Usage: %s operande1 {+|-|*|/} operande2\n", argv[0]);
		return EXIT_FAILURE;
	}
	/* il faut eviter la division par zero */
	if (argv[2][0]=='/' && argv[3][0]=='0') {
		printf("Erreur: Division par zero\n");
		exit(-1);
	}

	int cle =ftok(name,0);

	msg_id = msgget(cle,IPC_CREAT);
	if(msg_id == -1){
		perror("accès à la file\n");
		return EXIT_FAILURE;
	}

	printf("CLIENT %d: preparation du message contenant l'operation suivante:\
			%d %c %d\n", getpid(), atoi(argv[1]), argv[2][0], atoi(argv[3]));
	/* On prepare un message de type 1 à envoyer au serveur avec les
	 * informations necessaires */
	msg.type =1;
	msg.nomee.pid= getpid();
	msg.nomee.operande1 = atoi(argv[1]);
	msg.nomee.operateur =argv[2][0];
	msg.nomee.operande2 = atoi(argv[3]);
	printf("msg op 1 :%d \n",msg.nomee.operande1);
	printf("msg op 2 :%d \n",msg.nomee.operande2);

	/* A COMPLETER */
	printf("CLIENT: Envoi de la requête au serveur\n");
	/* envoi du message */
	if (msgsnd(msg_id, &msg, sizeof(msg.nomee), 0) == 0)
	{
		printf("CLIENT: Envoi réussi \n");
	}

	/* reception de la reponse */
	while(msgrcv(msg_id, &msg, sizeof(msg.nomee), getpid(), 0) == -1);
	printf("CLIENT: résultat reçu depuis le serveur %d : %d\n",msg.nomee.pid,msg.nomee.operande1);
	return EXIT_SUCCESS;
}
