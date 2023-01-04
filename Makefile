all: quorridor board.o list.o

list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

quorridor: quorridor.c board.c list.c board.h list.h item.h
	gcc -o quorridor quorridor.c board.c list.c

clean: 
	rm *.o quorridor


