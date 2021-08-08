# cub3d

## Features
My first ray-casting project inspired by the world-famous eponymous 90’s game, which was the first FPS ever.

| Program name | cub3D |
| ---- | ---- |
| Makefile | all, clean, fclean, re |
| Arguments | a map in format *.cub |
| External functs | • open, close, read, write, printf, malloc, free, perror, strerror, exit<br>• All functions of the math library (-lm man man 3 math)<br>• All functions of the MinilibX |
| Description | You must create a “realistic” 3D graphical representation of the inside of a maze from a first person perspective. You have to create this representation using the Ray-Casting principles mentioned earlier. |

You can explore the maze with WASD key and left/right arrow. Also you can choose wall, sprite and color of ceil and floor.

## Requirement
- gcc compiler
- MacOS

## Usage
Clone this repository:
```shell
git clone https://github.com/sakku-14/cub3d
```

Generate ***cub3d***:
```shell
make
```

Run ***cub3d***:
```shell
./cub3d maps/map.cub
```

You can also edit ***map.cub*** or create other ***.cub files***:

There are 9 elements in .cub file.
- ***Resolution***
  - Identifier: ***R***
  - Has two num of x and y render size
- ***North texture***
  - Identifier: ***NO***
  - Has path to the north texture
- ***South texture***
  - Identifier: ***SO***
  - Has path to the south texture
- ***West texture***
  - Identifier: ***WE***
  - Has path to the west texture
- ***East texture***
  - Identifier: ***EA***
  - Has path to the east texture
- ***Sprite texture***
  - Identifier: ***S***
  - Has path to the sprite texture
- ***Floor color***
  - Identifier: ***F***
  - Has R,G,B colors number(0-255): ex) 0, 255, 255 
- ***Ceilling color***
  - Identifier: ***C***
  - Has R,G,B colors number(0-255): ex) 0, 255, 255
- ***Map***
  - Identifier: None
  - 0: Floor
  - 1: Wall
  - 2: Sprite
  - N,S,W,E: player(place and looking the direction of North, South, West, East)
  - Space is validated but any other characters are forbidden.
  - Must be sorrounded by wall.

Example of .cub file:

![map](https://github.com/sakku-14/image_repo/blob/master/cub3d/map_img.png)

## Note

You can create map and move around in the maze freely.

The following is image of what you can do on this program:

![mov2](https://user-images.githubusercontent.com/65479630/128629087-29af9734-c29a-4246-b12e-8294a7afff37.gif)


## Author
- Yuki Sakuma
