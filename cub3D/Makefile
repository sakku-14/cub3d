# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysakuma <ysakuma@student.42tokyo.j>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/09 12:55:15 by ysakuma           #+#    #+#              #
#    Updated: 2021/03/20 17:46:22 by ysakuma          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f
CUBSRCDIR		= ./srcs/
CUBINCDIR		= ./includes/
GNLINCDIR		= ./get_next_line/
CUBSRCNAME		= bmp.c \
					exit_game.c \
					normalize_angle.c \
					cast_all_rays.c \
					first_conf.c \
					pack_line_core.c \
					cast_map_has_sprite_at.c \
					free_exit.c \
					pack_path.c \
					cast_set_horz.c \
					gen3d_describe.c \
					pack_rgb.c \
					cast_set_vert.c \
					gen3d_set_sprite.c \
					pack_update_flag.c \
					check_map.c \
					generate3d.c \
					pack_win_size.c \
					check_pack_map_str.c \
					get_conf.c \
					rendering.c \
					check_pack_map_utils.c \
					get_sprite_info.c \
					set_ray_facing.c \
					check_path.c \
					key_control.c \
					setting_img.c \
					check_rgb.c \
					main.c \
					setting_window.c \
					dist.c \
					map_has_wall.c \
					sort_sprite.c \
					error_mes.c \
					move.c \
					sprite.c
GNLSRCNAME		= get_next_line.c \
					get_next_line_utils.c
CUBSRCS			= ${addprefix ${CUBSRCDIR}, ${CUBSRCNAME}}
GNLSRCS			= ${addprefix ${GNLINCDIR}, ${GNLSRCNAME}}
CUBOBJS			= ${CUBSRCS:.c=.o}
GNLOBJS			= ${GNLSRCS:.c=.o}
FRAMEWORK		= -framework OpenGL -framework AppKit
LIBFTDIR		= ./libft
LIBFT			= ./libft.a
MLXDIR			= ./minilibx_mms_20200219
MLX				= ./libmlx.dylib

.c.o:
					${CC} ${CFLAGS} -I ${CUBINCDIR} -I ${GNLINCDIR} -c $< -o ${<:.c=.o}

$(NAME):			$(CUBOBJS) $(GNLOBJS)
					$(MAKE) -C $(LIBFTDIR)
					cp libft/libft.a ./
					$(MAKE) -C $(MLXDIR)
					cp minilibx_mms_20200219/libmlx.dylib ./
					${CC} ${CFLAGS} ${FRAMEWORK} ${LIBFT} ${MLX} -o ${NAME} ${CUBOBJS} ${GNLOBJS}

all:				$(NAME)

clean:
					$(MAKE) -C $(LIBFTDIR) clean
					$(MAKE) -C $(MLXDIR) clean
					${RM} ${CUBOBJS} ${GNLOBJS}

fclean:				clean
					$(MAKE) -C $(LIBFTDIR) fclean
					${RM} $(LIBFT) $(MLX)
					${RM} ${NAME}

re:					fclean all

.PHONY:				all clean fclean re
