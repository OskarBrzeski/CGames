build:
	mkdir -p ./bin
	cc -o ./bin/main ./src/main.c -lm -lraylib
