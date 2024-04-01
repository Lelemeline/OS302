#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void fils(int i_fils){
    pid_t pid_fils = getpid();
    pid_t pid_pere = getppid();
    printf("pid processus père %d et processus fils :  %d\n",pid_pere, pid_fils);
    sleep(2*i_fils);
    exit(0);
}
void pere(void){
    int ret_fils,etat;
    while ((ret_fils = wait(&etat)) != -1) {
        printf("Processus fils %d terminé avec l'état : %d\n", ret_fils, WEXITSTATUS(etat));
    }
    printf("C'est la fin\n");
    exit(0);
}


int main (int argc, char *argv[])
{
    int Nbre_de_Proc, i_fils, pid_fils;
    if (argc != 2) /* On utilise un seul parametre */
    {
        printf(" Utilisation : %s nbre-de-processus ! \n", argv[0]);
        exit(2);
    }
    //1. lecture sur la ligne de commande du nombre N de processus à créer
    Nbre_de_Proc = atoi (argv [1]); /* conversion ascii -> entier */
    /* ----------------------------------------
    * creation des processus fils
    * ----------------------------------------
    */
    for ( i_fils =1; i_fils <= Nbre_de_Proc ; i_fils++ )
    {
        pid_fils = fork(); //2. Création de N processus fils
        switch (pid_fils){
            case 0 :
                fils(i_fils);
                break;
            case -1 :
                perror("Le fork n'a pas reussi ");
                exit(33); /* si erreur -> fin du pere ! */
        }
    }
    /* --------------------------------------------
    * Dans la fonction pere, on utilisera le
    * fait que wait renvoie la valeur -1 quand
    * il n'y a plus de processus fils a attendre.
    * --------------------------------------------
    */
    pere();
    return 0;
}