#ifndef __CALCUL_H__
#define __CALCUL_H__
#define MSGKEY 50
#define NSIG 64
#include <sys/types.h>
struct msg_struct {
    long type;
    
    struct nomee 
    {
        int operande1;
        int operande2;
        char operateur;
        pid_t pid;
    }nomee;
    
};

#endif /* __CALCUL_H__ */
