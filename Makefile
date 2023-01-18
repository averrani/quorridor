all: quorridor board.o list.o player.o

graphic: graphicQuorridor board.o list.o player.o

list.o: list.c list.h
	gcc -c list.c

board.o: board.c board.h
	gcc -c board.c

player.o: player.c player.h 
	gcc -c player.c

quorridor: quorridor.c board.c list.c board.h list.h item.h player.c player.h 
	gcc -o quorridor quorridor.c board.c list.c player.c

graphicQuorridor: graphicQuorridor.c quorridor.c board.c list.c board.h list.h item.h player.c player.h 
	gcc -o graphicQuorridor -lSDL -lSDL_image graphicQuorridor.c `sdl2-config --cflags --libs`

testSDL: testSDL.c quorridor.c board.c list.c board.h list.h item.h player.c player.h
	gcc -o testSDL testSDL.c `sdl2-config --cflags --libs`

clean: 
	rm *.o quorridor



# Installer sdl2 : 

# sudo apt-get install libsdl2-2.0-0 libsdl2-dbg libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dbg libsdl2-image-dev

# et/ou

# sudo apt-get update
# sudo apt-get install libglm-dev
# sudo apt-get install libglew-dev
# sudo apt-get install libsdl2-dev

#Pour tester que sdl2 fonctionne correctement :

#make testSDL puis ./testSDL

