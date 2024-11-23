# CGames

This is a collection of basic games written in C and using Raylib.

## Completed Games

The following games are in a playable state, but may contain some bugs:

- Pong
- Snake

## Planned Games

I plan to create basic recreations of the following games:

- Tetris
- osu!
- Minecraft

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
