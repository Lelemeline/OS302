/*********************************************************************
 * OS302 - shm - Exercice 1                                          *
 * Utilisation des segments de memoire partagee                      *
 *********************************************************************/
#include "segment_memoire.h"

/* Cree un segment de memoire
 * taille : la taille du segment memoire a creer
 * nom    : le nom du fichier associe
 * cle    : associe au nom pour la construction d'une cle identifiant
 *          le segment memoire (on utilisant la fonction ftok)
 * retourne : l'identificateur du segment, ou -1 en cas d'erreur */
int cree_segment(int taille, char* nom, int cle){
    key_t mem_clef;
    if((mem_clef = ftok(nom,cle))==-1){
      perror("Erreur de création de clé");
      exit(EXIT_FAILURE);
    }
    int segment;
    if((segment = shmget(mem_clef, taille, IPC_CREAT|0644))==-1){
      perror("Erreur de création de segment");
      exit(EXIT_FAILURE);
    }
    return segment ; //en cas de succès, shmget retourne l'identifiant du segment mémoire créé. Sinon, elle retourne -1 .
}

/* Afficher toutes les informations concernant un segment de memoire
 * shmid : l'identificateur du segment
 * retourne -1 en cas d'erreur */
int afficher_info_segment(int shmid){
  struct shmid_ds struct_donnee ;
  if(shmctl(shmid,IPC_STAT,&struct_donnee)==-1){
    perror("Erreur de shmctl");
    exit(EXIT_FAILURE);
  }
  printf("\033[37;01m===================Affichage des informations du segment========================\033[00m\n");
  printf("Clé : %i\n",struct_donnee.shm_perm.__key);
  printf("PID creator : %i\n",struct_donnee.shm_cpid);
  printf("Taille du segment [octet] : %li\n",struct_donnee.shm_segsz);
  printf("UID effectif du propriétaire : %i\n", struct_donnee.shm_perm.uid);
  printf("Mode : %i\n",struct_donnee.shm_perm.mode);

  return 0 ;
}

// avec IPC_STAT
      // struct shmid_ds {
      //          struct ipc_perm shm_perm;    /* Ownership and permissions */
      //          size_t          shm_segsz;   /* Size of segment (bytes) */
      //          time_t          shm_atime;   /* Last attach time */
      //          time_t          shm_dtime;   /* Last detach time */
      //          time_t          shm_ctime;   /* Last change time */
      //          pid_t           shm_cpid;    /* PID of creator */
      //          pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
      //          shmatt_t        shm_nattch;  /* No. of current attaches */
      //          ...
      //      };


/* Detruie un segment de m�moire
 * shmid : l'identificateur du segment
 * retourn -1 en cas d'erreur */
int detruire_segment(int shmid){

}

int main() {
  int shmid ;
  char *nom = (char *) malloc(100*sizeof(char)) ;
  nom = "exo1.c" ;
  shmid = cree_segment(100,nom,2) ;
  afficher_info_segment(shmid) ;
  //detruire_segment(shmid) ;
  return 0 ;
}
