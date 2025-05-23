# CGames

This is a collection of basic games written in C and using
[Raylib](https://github.com/raysan5/raylib). I am developing this as
practice in using the C programming language.

## Completed Games

The following games are in a playable state, but may contain some bugs:

- Pong
- Snake
- Tetris
- 2048

## Planned Games

I plan to create basic recreations of the following games:

- osu!
- Civilization
- Minecraft
- Counter Strike

This list will gradually expand as I finish more of these games.

## Build

Currently, this build is for Linux only.

First, clone this repository and enter the directory.

```bash
git clone https://github.com/OskarBrzeski/CGames.git
cd CGames
```

Raylib is already included in the repository so you do not need to download or
install it yourself. You can find this in the `raylib` directory.

This project uses `make` to build the program. Run the following command
to build and start the program.

```bash
make run
```

Run the following command to remove all object files and the executable.

```bash
make clean
```

The make configuraion can be found in the `Makefile` file.

## Development

If you are using clangd as your LSP, you may want to use `bear` to create a
compilation database.

```bash
bear -- make
```
