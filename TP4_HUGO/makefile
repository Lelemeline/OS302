main : client1 client2 serveur1 serveur2
	make client1
	make client2
	make serveur1
	make serveur2
	make clean


serveur1 : serveur1.o
	gcc -o $@ $^ -Wall -Wextra

serveur1.o : serveur1.c calcul.h
	gcc -c -Wall -Wextra $^

client1 : client1.o
	gcc -o $@ $^ -Wall -Wextra

client1.o : client1.c calcul.h
	gcc -c -Wall -Wextra $^


serveur2 : serveur2.o
	gcc -o $@ $^ -Wall -Wextra

serveur2.o : serveur2.c trad.h
	gcc -c -Wall -Wextra $^


client2 : client2.o
	gcc -o $@ $^ -Wall -Wextra

client2.o : client2.c trad.h
	gcc -c -Wall -Wextra $^

clean :
	rm *.o
	rm *.h.gch
	clear
