build:
	gcc -g -L../minilibx_mms_20200219 -L../minilibx_opengl_20191021 -L./get_next_line -L./libft -framework OpenGL -framework AppKit libmlx.a libmlx.dylib ./src/*.c ./get_next_line/*.c ./libft/*.c -o raycast;

run:
	./raycast map_1.cub;

clean:
	rm raycast raycast.dSYM;
