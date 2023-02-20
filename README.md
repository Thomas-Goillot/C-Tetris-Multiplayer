# Tetris Multiplayer

> Tetris Multiplayer is a multiplayer version of the classic game Tetris. It is written in C and uses the SDL2 library for graphics and sound.

> It is a school project for the 2nd year of ESGI (Ecole Supérieure de Génie Informatique) in Paris.

> This project was made in a group of 3 people.

> The main purpose of this project is to recreate the classic game Tetris in C and in the same time create a server that will save players' scores and display the 5 first top scores in the game.


## Requirements
- make
- gcc

## Installation

### Windows 

```bash
git clone https://github.com/Thomas-Goillot/C-Tetris-Multiplayer
cd C-Tetris-Multiplayer
mkdir obj
make
```

### Linux

```bash
Not implemented yet. :(
```

## Usage

```bash
./server
```
>In another terminal

```bash
./menu <yournameinthegame>
```

## Used libraries

- [SDL2](https://www.libsdl.org/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [SDL_render](https://wiki.libsdl.org/SDL_RenderCopy)
- [winsock2](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2)

## Issues

- Logic of the game (Algorithm)
- Server (Socket)
- Menu (SDL2)
- Issues using modulation compilation and SDL2 library (Still not working)

## Authors / Contributors

- [Joshua Tang Tong Hi](https://github.com/Joshua-Tangtonghi)
- [Ibrahim Oubihi](https://github.com/Ibrahim-Oubihi)
- [Thomas Goillot](https://github.com/Thomas-Goillot)


## Who done what ?

- Thomas Goillot : Server, Game Logic, Game Graphics, menu
- Joshua Tang Tong Hi : Game Logic, Game Graphics, menu
- Ibrahim Oubihi : Server, Game Logic, Game Graphics

>Using git was use partially, so the commit history is not accurate and does not represent the real work done by each member of the team.



