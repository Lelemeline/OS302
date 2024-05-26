#include "calcul.h"

int main(void){

    // création de clé
    char *cle = "clef";
    key_t clef = ftok(cle,2);

    // ouverture de file
    int file = msgget(clef,0);
    // 0X662 : permissions accordées ( dans l'ordre g o u) permission suprême = 0x666

    // récupération du message et du pid
    struct msg_struct message;
    pid_t pid = getpid();

    // récupération des opérandes
    message.operation.pid_client = pid;
    message.type = 1;
    message.operation.op1 = 2;
    message.operation.op2 = 4;
    message.operation.operande = '+' ;

    // envoi du message avec opération

    if(msgsnd(file,&message,sizeof(struct operation),1) == -1){
        perror("Erreur d'envoi");
    }

    // récupération du résultat
    if(msgrcv(file,&message,sizeof(struct operation),pid,0)==0){
            printf("Message reçu\n");
    }
    printf("Le résultat de l'opération est %i\n",message.operation.resultat);


}