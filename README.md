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


## Authors / Contributors

- [Joshua Tang Tong Hi](https://github.com/Joshua-Tangtonghi)
- [Ibrahim Oubihi](https://github.com/Ibrahim-Oubihi)
- [Thomas Goillot](https://github.com/Thomas-Goillot)


## Who done what ?


![Who done what ?](https://raw.githubusercontent.com/Thomas-Goillot/C-Tetris-Multiplayer/master/Image/who_done_what.png?raw=true)

- Thomas Goillot :
>During the project, I was responsible for creating the server using socket programming. I spent a lot of time researching and implementing the best socket techniques to ensure a smooth and efficient communication between the server and the clients. In addition to that, I also created the score system and the top 5 scores functionality that allowed players to compete against each other. To make sure everyone had access to the project, I also created the git repository and regularly updated it with new features and improvements. 

>I enjoyed working on the project and seeing the game come together as a whole. I also learned a lot about socket programming and how to use it in C. I improved my teamwork skills and learned how to work in a group to create a project from scratch. I also learned how to use the SDL2 library and improve my ability to create makefiles and use modulation compilation. Overall, I had a lot of fun working on the project and I am proud of the result.

- Joshua Tang Tong Hi :
>As part of the team that developed the Tetris game, I was responsible for creating the menus, designing the game itself and implementing the grid. I had to consider several factors while designing the menus and ensure that they were easy to navigate and visually appealing. The game design was challenging, but I enjoyed creating the graphics and visual effects that make the game engaging and enjoyable. I also added the tetrominos music to enhance the user experience, creating an immersive and enjoyable game environment. Finally, I created the grid that the tetriminos fell on, ensuring that the game logic was followed and everything worked smoothly.

>The project aligns with my training, especially with the development part. The training at ESGI helped me to code better and achieve my goals. I enjoyed this project because it was a challenging experience where I learned a lot, and I also enjoyed working with a team

- Ibrahim Oubihi :
>During the Tetris project, I worked on the creation of the shapes of the tetriminos, the rotation of the tetriminos and the logic of the game. It was my responsibility to create the various shapes that the tetriminos could take, and to make sure that they were visually distinct and easy to recognize. Additionally, I worked on implementing the rotation of the tetriminos and ensuring that the game logic was followed, so that players could rotate the pieces as needed. I enjoyed working on the project and seeing everything come together as a cohesive game.

>For my part, this project allowed me to develop my research capacity in a project in particular for the understanding of the algorithm of the game and the creation of forms, as well as the use of SDL.
This project was very complicated and required a lot of personal work but allowed me to learn a lot of things, in particular the use of git as well as sdl and my skills in the c language, in particular at the level of the logic of the algorithm.

## What we learned / What we improved

- Socket programming
- SDL2 library
- Git
- Teamwork
- C
- makefile
- Modulation compilation

## Issues

- Logic of the game (Algorithm)
- Server (Socket)
- Menu (SDL2)
- Partialy using modulation compilation, SDL2 library and makefile

### How we fixed it :
- We used a lot of time to understand how the game works and how to implement it in C.
- Researching and implementing the best socket techniques to ensure a smooth and efficient communication between the server and the clients.
- We spend lots of time to understand how the SDL2 library works and how to use it.
- We used the docs of our teacher to understand how to use the makefile and the modulation compilation. We also reused our training exercises to understand how to use it.

## Disclaimer
>We start using git in the middle of the project, so the commit history is not accurate and does not represent the real work done by each member of the team. In fact we started learning git in the middle of the project and we did not use it properly. We are sorry about that. We will do better next time ! :)







