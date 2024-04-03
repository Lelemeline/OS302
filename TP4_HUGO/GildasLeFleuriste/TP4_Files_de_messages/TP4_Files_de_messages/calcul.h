#ifndef __CALCUL_H__
#define __CALCUL_H__

struct messageC{
    int pid;
    char operation;
    int operande1, operande2;
};

struct msg_struct {
    long type;
    struct messageC message;
};






#endif /* __CALCUL_H__ */
