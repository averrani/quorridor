all: Quorridor Board.o List.o

List.o: List.c List.h
	gcc -c List.c

Board.o: Board.c Board.h
	gcc -c Board.c -o Board.o

Quorridor: Quorridor.c Board.c List.c Board.h List.h Item.h Player.h 
	gcc -o Quorridor Quorridor.c Board.c List.c

Item.o: Item.h
	gcc -o Item.h

clean: 
	rm *.o Quorridor


