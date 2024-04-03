#include <sys/types.h>

struct msg_TRAD_struct {
    long type;
    struct trad
    {
        pid_t pid;
        int taille;
        char message[];
    }trad;
};