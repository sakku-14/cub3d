all:
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit test4.c
	./a.out
