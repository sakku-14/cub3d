build:
	gcc -Wall -Werror -Wextra -g -L../minilibx_mms_20200219 -L../minilibx_opengl_20191021 -L./get_next_line -L./libft -framework OpenGL -framework AppKit libmlx.a libmlx.dylib ./srcs/*.c ./get_next_line/*.c ./libft/*.c -o cub3D;

run:
	./cub3D ./maps/map_1.cub;

clean:
	rm -rf cub3D cub3D.dSYM;
