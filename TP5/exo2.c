/*********************************************************************
 * OS302 - shm - Exercice 2                                          *
 * Utilisation des segments de memoire partagee                      *
 *********************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "segment_memoire.h"

int main(int argc, char *argv[]) {
  //définition des variables
  int pid;      // le PID du processus
  char *mem;    // pointeur vers le segment memoire
  int shmid;    // l'identificateur du segment memoire
  char *nom = (char *) malloc(15*sizeof(char));
  strcpy(nom, "exo2.c");
  int cle = 2 ;
  int status;
  if(argc!=2){
    perror("Usage : ./exo2 texte");
    exit(EXIT_FAILURE);
  }

  // creation du segment de memoire partagee
  if((shmid = cree_segment(100,nom,cle))==-1){
    perror("Création du segment mémoire");
    exit(EXIT_FAILURE);
  }

  // creation du processus fils
  pid = fork();
  if (pid == -1) {
    perror("impossible de creer un processu fils!");
    exit(-1);
  }
  else if (pid == 0) {
    sleep(2);
    // je suis le fils!
    // a completer : s'attacher au segment et affichage de son contenu
    mem =shmat(shmid,NULL,SHM_RDONLY);
    printf("Contenu du segment mémoire : %s\n",mem);
  }
  else {
    // je suis le pere!
    // a completer : attachement et ecriture sur le segment de memoire partagee
    // a completer : attendre la fin du fils + detacher le segment et le detruire
    // ...
    mem = shmat(shmid,NULL,0);
    strncpy(mem, argv[1], strlen(argv[1]));
    pid_t ret ;
    if((ret = waitpid(pid, &status, WUNTRACED ))==-1){
      perror("erreur de wait");
    }


  shmdt(mem);
  shmctl(shmid, IPC_RMID, 0);
  }
  free(nom);

  return 0 ;
}
