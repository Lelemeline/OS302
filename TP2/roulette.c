#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_MAX 20
#define via "barillet.txt"

int lire_valeur(const char *path)
{
  FILE *fichier;
  char chaine[TAILLE_MAX];
  int valeur;
  fichier = fopen(path, "r");
  if (fichier != NULL) {
    /* On lit au maximum TAILLE_MAX caractères du fichier, ce qui est lu est stocké dans `chaine` */
    fgets(chaine, TAILLE_MAX, fichier);
    fclose(fichier);
    valeur = atoi(chaine);
  }
  return valeur;
}

void ecrire_valeur(const char *path, int valeur)
{
  FILE *fichier = fopen(path, "w");
  if (fichier != NULL) {
    fprintf(fichier, "%d", valeur);
    fclose(fichier);
  }
}

int main(void){
    pid_t pid[6]; // gestion et sauvegarde des pids des processus fils
    pid_t pid_fils ;
    srand(time(NULL)); // initialisation de la fonction rand
    for(int i = 0; i<6 ; i++){
        switch(pid_fils = fork()){
            case -1 : //erreur de création
                perror("fork error") ; break;
            case 0 : // processus fils
                printf("Je suis le fils n°%i avec le pid %d\n",i+1,getpid());
                exit(0);
            break;
            default : // processus père
                pid[i] = pid_fils; // stockage des pids des processus fils
            break;
        }
    }
    int valeur = (int) rand()%7; // on choisit un indice au hasard pour tuer un processus fils
    ecrire_valeur(via,valeur);
    for(int i= 0;i<6;i++){
        int numero = lire_valeur(via);
        if(numero != i+1){ // lecture du barillet
            printf("Je suis le fils n°%i de pid %d et je ne suis pas mort\n",i+1,pid[i]);
        }
        else{
            exit(0);
        }

    }
    for(int i = 0; i < 6; i++) {
        wait(NULL); //attente de l'arrêt du jeu.
    }
    exit(0);
}