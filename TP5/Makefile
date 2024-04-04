main : exo2 exo1
	make exo1
	make exo2
	make clean

exo2 : exo2.o segment_memoire.o
	gcc -o $@ $^ -Wall -Wextra

exo2.o : exo2.c segment_memoire.h
	gcc -c -Wall -Wextra $< -o $@

exo1 : exo1.o segment_memoire.o
	gcc -o $@ $^ -Wall -Wextra

exo1.o : exo1.c segment_memoire.h
	gcc -c -Wall -Wextra $< -o $@

segment_memoire.o : segment_memoire.c segment_memoire.h
	gcc -c -Wall -Wextra $< -o $@

clean :
	rm *.o
	clear

tar :
	find . -type f -executable -exec rm {} +
	cd
	tar -cvf MICHEL_TAVIER_OS302_TP4_EISGRP2.tar *