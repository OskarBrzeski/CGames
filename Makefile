LIBS = -I./raylib/ -L./raylib/ -l:libraylib.a -lm

run: build
	./bin/main

build: main.o menu.o pong.o snake.o
	mkdir -p ./bin
	cc -o ./bin/main main.o menu.o pong.o snake.o ${LIBS}

main.o: ./src/main.c
	cc -c ./src/main.c ${LIBS}

menu.o: ./src/menu/menu.c
	cc -c ./src/menu/menu.c ${LIBS}

pong.o: ./src/pong/pong.c
	cc -c ./src/pong/pong.c ${LIBS}

snake.o: ./src/snake/snake.c
	cc -c ./src/snake/snake.c ${LIBS}

clean:
	rm ./*.o ./bin/main
	rmdir ./bin
