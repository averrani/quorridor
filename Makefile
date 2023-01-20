all: quorridor player.o board.o list.o 

graphic: graphicQuorridor board.o list.o player.o

quorridor: quorridor.c board.o list.o player.o
	gcc -g -o quorridor quorridor.c board.c list.c player.c

graphicQuorridor: graphicQuorridor.c quorridor.c board.o list.o player.o
	gcc -g -o graphicQuorridor graphicQuorridor.c  -lSDL2 -lSDL2_image

testSDL: testSDL.c quorridor.c board.o list.o player.o
	gcc -g -o testSDL testSDL.c 

board.o: board.c board.h
	gcc -g -c board.c

player.o: player.c player.h
	gcc -g -c player.c

list.o: list.c list.h 
	gcc -g -c list.c

clean: 
	rm *.o quorridor graphicQuorridor testSDL



# Installer sdl2 : 

# sudo apt-get install libsdl2-2.0-0 libsdl2-dbg libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dbg libsdl2-image-dev

# et/ou

# sudo apt-get update
# sudo apt-get install libglm-dev
# sudo apt-get install libglew-dev
# sudo apt-get install libsdl2-dev

#Pour tester que sdl2 fonctionne correctement :

#make testSDL puis ./testSDL

