CFLAGS=-Wall -g
./build/objgame: ./build/object.o ./build/objgame.o
	cc -o ./build/objgame ./build/object.o ./build/objgame.o
./build/object.o: ./src/object.c
	cc -c -o ./build/object.o ./src/object.c
./build/objgame.o: ./src/objgame.c
	cc -c -o ./build/objgame.o ./src/objgame.c
clean:
	rm -f ./build/*