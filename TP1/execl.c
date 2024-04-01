#include <unistd.h>
#include <stdio.h>
int main (void) {
	printf("Coucou, ici %d !\n", getpid() );
	sleep (4);
	return 6;
}
