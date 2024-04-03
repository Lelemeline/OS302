#include <sys/types.h>

struct texte{
    pid_t pid;
    int taille;
    char message[];
};

struct msg_struct {
    long type;
    struct texte txt;
};