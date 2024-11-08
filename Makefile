build: main.o pong.o
	mkdir -p ./bin
	cc -o ./bin/main main.o pong.o -lm -lraylib

main.o: ./src/main.c
	cc -c ./src/main.c

pong.o: ./src/pong/pong.c
	cc -c ./src/pong/pong.c

clean:
	rm *.o
