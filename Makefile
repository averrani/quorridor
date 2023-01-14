all: quorridor board.o list.o player.o

list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

player.o: player.c player.h 
	gcc -c player.c

quorridor: quorridor.c board.c list.c board.h list.h item.h player.c player.h 
	gcc -o quorridor quorridor.c board.c list.c player.c

clean: 
	rm *.o quorridor

