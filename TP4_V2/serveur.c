#include "calcul.h"

int file;

void handle(int signal){
    printf("Server is killed\n");
    msgctl(file,IPC_RMID,NULL);
    if(signal == SIGINT) exit(EXIT_SUCCESS);
}

int main(void){
    for(int i =0 ; i<_NSIG;i++){
        signal(i,handle);
    }
    // création de clé
    char *cle = "clef";
    key_t clef = ftok(cle,2);
        struct msg_struct message;
    // création de file
    file = msgget(clef,IPC_CREAT| 0400 | 0200);
    if(file == -1){
        perror("Erreur file");
        handle(SIGINT);
        exit(-1);
    }
    // IPC_CREAT : crée une file de message
    // IPC_EXCL : plante si la file de message existe déjà
    // 0X666 : permissions accordées ( dans l'ordre g o u) permission suprême = 0x666

    while(1){
        // récupération du message et test de type

        if(msgrcv(file,&message,sizeof(struct operation),1,0)==-1){
            perror("Erreur de réception");
            handle(SIGINT);
        }
        else{
            // récupération des opérandes et calcul
            int resultat;

            switch(message.operation.operande){
                case '+': resultat = message.operation.op1 + message.operation.op2; break;
                case '-': resultat = message.operation.op1 - message.operation.op2;break;
                case '*': resultat = message.operation.op1 * message.operation.op2;break;
                case '/':
                    if(message.operation.op2 == 0){perror("Division par zéro");}
                    resultat = message.operation.op1 /message.operation.op2;
                    break;
            }
            message.operation.resultat = resultat;
            message.type = message.operation.pid_client;
            // envoi du message avec résultat

            if(msgsnd(file,&message,sizeof(struct operation ),0) == 0){
               printf("Envoi réussi\n");
            }

        }
    }

}