LIBS = -I./raylib/ -L./raylib/ -l:libraylib.a -lm

run: build
	./bin/main

build: main.o menu.o utils.o pong.o snake.o tetris.o tofe.o
	mkdir -p ./bin
	cc -o ./bin/main main.o menu.o utils.o pong.o snake.o tetris.o tofe.o ${LIBS}

main.o: ./src/main.c
	cc -c ./src/main.c ${LIBS}

menu.o: ./src/menu/menu.c
	cc -c ./src/menu/menu.c ${LIBS}

utils.o: ./src/utils/utils.c
	cc -c ./src/utils/utils.c ${LIBS}

pong.o: ./src/pong/pong.c
	cc -c ./src/pong/pong.c ${LIBS}

snake.o: ./src/snake/snake.c
	cc -c ./src/snake/snake.c ${LIBS}

tetris.o: ./src/tetris/tetris.c
	cc -c ./src/tetris/tetris.c ${LIBS}

tofe.o: ./src/tofe/tofe.c
	cc -c ./src/tofe/tofe.c ${LIBS}

clean:
	rm ./*.o ./bin/main
	rmdir ./bin
