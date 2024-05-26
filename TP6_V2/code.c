#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <err.h>
#include <stdlib.h>

int main(void){
    pid_t pid = 15;
    int n = 10 ; // nombre de fils que l'on veut créer
    while(pid!=0 && n >0){
        pid = fork();
        if(pid == -1){
            perror("Erreur de fork");
        }
        n-=1;
    }
    switch(pid){
        case 0 : // fils
            // comportement du fils à s'installer
            printf("Je suis le fils %i de pid %i, mon père est %i\n",n, getpid(),getppid());
            break;
        default : // père
            // comportement du père
            printf("%i \n",n);
            break;
    }
    //printf("On a crée %i fils, on s'arrête là\n",n);
    exit(0);

}


// code plus joli

int main(void){
    pid_t pid = 6 ;
    int n = 10;
    while((pid = fork())!=0 && n>0){
        n-=1;
    }
    if(pid == 0){
        Codefils();
    }
    Codepere();
    exit(0);

}