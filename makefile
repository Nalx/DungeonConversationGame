all: practica3
main.o: main.c logica.h
	gcc -ggdb -Wall -Wextra -c main.c
cua.o: cua.c cua.h enemics.h
	gcc -ggdb -Wall -Wextra -c cua.c
classe.o: classe.c classe.h
	gcc -ggdb -Wall -Wextra -c classe.c
enemics.o: enemics.c enemics.h
	gcc -ggdb -Wall -Wextra -c enemics.c
herois.o: herois.c herois.h classe.h enemics.h cua.h logica.h
	gcc -ggdb -Wall -Wextra -c herois.c
logica.o: logica.c logica.h herois.h classe.h enemics.h cua.h
	gcc -ggdb -Wall -Wextra -c logica.c

practica3: main.o logica.o classe.o  herois.o enemics.o cua.o
	gcc main.o classe.o enemics.o herois.o logica.o cua.o -o practica3

clean: 
	rm -f *.o practica3
