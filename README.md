# cub3d

## Features
My first ray-casting project inspired by the world-famous eponymous 90’s game, which was the first FPS ever.

| Program name | cub3D |
| ---- | ---- |
| Makefile | all, clean, fclean, re |
| Arguments | a map in format *.cub |
| External functs | • open, close, read, write, printf, malloc, free, perror, strerror, exit<br>• All functions of the math library (-lm man man 3 math)<br>• All functions of the MinilibX |
| Return value | 1 : A line has been read<br>0 : EOF has been reached<br>-1 : An error happened |
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
| TH1 | TH2 |
----|---- 
| TD1 | TD3 |
| TD2 | TD4 |


## Note

## Author
- Yuki Sakuma
