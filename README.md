# OS302

## TP1
[01/04]
Premier TP : un peu chill; 
On joue avec des processus, et des pid, c'est marrant, c'est sympa.
Attention à ne pas tuer ses parents, ses grands-parents et sa famille adoptive ( je cite Arthur Baudet)
Sinon, on finit vite par buter sa session, et un écran tout noir.

## TP2
[01/04]
Le code du barillet est pas du tout garanti, mais il est ce qu'il est.
À ce jour, je n'ai pas eu le temps de m'y replonger et l'OS c'est pas une de mes facilités.

## TP3
[01/04]
Code comm visiblement bon ( coup de chance ). Super aide d'internet pour le coup.
Client serveur pas très difficile hormis une difficulté : mon serveur attends seulement un texte d'un client, après ça il se ferme.
Sinon, il attendait indéfiniment mais sans lire ce que pouvaient envoyer les clients ( alors que ces derniers écrivaient bien dans le tube).
Résultat : plus d'une heure pour débuguer, j'ai fini par péter mon crâne.

[02/04]
  pour que le serveur lise en continu, il faut penser que le client ferme à chaque fin d'exécution son fichier fd,
à savoir le fichier que lit de l'autre côté le serveur...
Donc dans le while(1) on pense à rajouter l'ouverture du fichier.

Et j'ai rajouté non seulement une jolie présentation mais aussi un moeyn de fermer proprement le serveur.

## TP4
[03/04]
Version Hugo
client-serveur1 : fonctionne
client-serveur2 : mauvaise réception/traitement du message. À mon sens, vient de l'utilisation de msgrcv.

[03/04]
plus tard... Le client-serveur2 fonctionne, il fallait fixer une taille de chaine dans la structure msg.trad. ( je n'ai aps réussi sans)
Donc c'est fixé à 100, avec #define ( c'est pas si mal)
j'ai voulu un peu délirer donc y a une jolie présentation avec un ptit makefile tout propre ( j'avais envie d'un taff  un peu propre)

# TP5
[03/04]
Exercice 1 fonctionne je crois. ( en tout cas compile et fonctionne maintenant est ce que y a pas une embrouille à la moi, jsp?)

