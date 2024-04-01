#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>


// la fonction getpwuid "remplit" une structure, qui nous permet d'accéder aux données nécessaires

int main(void){
	char *name = getlogin();
	uid_t uid = getuid();
	uid_t euid = geteuid();
	struct passwd* info_usr = getpwuid(uid);
	struct passwd* info_eusr = getpwuid(euid);
	printf("Reel\t : %s (UID = %i), %s(GID= %i)\n",info_usr->pw_name,info_usr->pw_uid,info_usr->pw_name,info_usr->pw_gid);
	printf("Effectif : %s (UID = %i), %s(GID= %i)\n",info_eusr->pw_name,info_eusr->pw_uid,info_eusr->pw_name,info_eusr->pw_gid);
}
