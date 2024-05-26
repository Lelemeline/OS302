#ifndef __CALCUL_H__
#define __CALCUL_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <signal.h>



struct operation {
    int op1;
    int op2;
    char operande;
    int resultat;
    pid_t pid_client;
};

struct msg_struct {
    long type;
    struct operation operation;
};


#endif /* __CALCUL_H__ */