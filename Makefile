LIBS = -I./raylib/ -L./raylib/ -lraylib -lm

run: build
	./bin/main

build: main.o menu.o utils.o pong.o snake.o tetris.o tofe.o
	mkdir -p ./bin
	cc -o ./bin/main main.o menu.o utils.o pong.o snake.o tetris.o tofe.o ${LIBS}

main.o: ./src/main.c ./src/main.h
	cc -c ./src/main.c ${LIBS}

menu.o: ./src/menu/menu.c ./src/menu/menu.h
	cc -c ./src/menu/menu.c ${LIBS}

utils.o: ./src/utils/utils.c ./src/utils/utils.h
	cc -c ./src/utils/utils.c ${LIBS}

pong.o: ./src/pong/pong.c ./src/pong/pong.h
	cc -c ./src/pong/pong.c ${LIBS}

snake.o: ./src/snake/snake.c ./src/snake/snake.h
	cc -c ./src/snake/snake.c ${LIBS}

tetris.o: ./src/tetris/tetris.c ./src/tetris/tetris.h
	cc -c ./src/tetris/tetris.c ${LIBS}

tofe.o: ./src/tofe/tofe.c ./src/tofe/tofe.h
	cc -c ./src/tofe/tofe.c ${LIBS}

clean:
	rm ./*.o ./bin/main
	rmdir ./bin
