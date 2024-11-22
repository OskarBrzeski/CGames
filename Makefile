run: build
	./bin/main

build: main.o menu.o pong.o snake.o
	mkdir -p ./bin
	cc -o ./bin/main main.o menu.o pong.o snake.o -lm -lraylib

main.o: ./src/main.c
	cc -c ./src/main.c

menu.o: ./src/menu/menu.c
	cc -c ./src/menu/menu.c

pong.o: ./src/pong/pong.c
	cc -c ./src/pong/pong.c

snake.o: ./src/snake/snake.c
	cc -c ./src/snake/snake.c

clean:
	rm *.o
