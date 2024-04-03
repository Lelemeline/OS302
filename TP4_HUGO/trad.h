#include <sys/types.h>
#define TAILLE_MAX 100

struct msg_TRAD_struct {
    long type;
    struct trad
    {
        pid_t pid;
        int taille;
        char message[TAILLE_MAX];
    }trad;
};
