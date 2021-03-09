/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakuma <ysakuma@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 19:44:31 by ysakuma           #+#    #+#             */
/*   Updated: 2021/03/09 14:57:10 by ysakuma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/constants.h"

/*
__attribute__((destructor))
void    end()
{
    system("leaks cub3D");
}
*/

int
	cub_checker(char *av)
{
	int i;

	i = 0;
	if (!av || !av[i])
		return (FALSE);
	while (av[i])
	{
		if (av[i] == '.')
		{
			if (!(ft_strncmp(&av[i], ".cub", 4)) && (ft_strlen(&av[i]) == 4))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int
	save_checker(char *av)
{
	if (av && *av)
	{
		if (ft_strncmp(av, "--save", 6) || !(ft_strlen(av) == 6))
			return (FALSE);
	}
	return (TRUE);
}

void
	init_vars(t_cub *cub)
{
	int i;

	ft_bzero(cub, sizeof(t_cub));
	i = 0;
	while (i < 9)
		ft_bzero(&(cub->conf.cub_flag[i++]), sizeof(int));
}

int
	initialize_window(t_cub *cub)
{
	if (!(cub->cub_ptr = mlx_init()))
		return (FALSE);
	if (!(cub->win = mlx_new_window(cub->cub_ptr, cub->conf.win_w \
								, cub->conf.win_h, "cub3d_window")))
		return (FALSE);
	return (TRUE);
}

int
	main(int ac, char **av)
{
	t_cub	cub;

	if (ac <= 1 || ac > 3)
		return (error_mes("Error\n few or too many args\n", ERROR));
	if ((ac == 3 && !save_checker(av[2])) || (!cub_checker(av[1])))
		return (error_mes("Error\n invalid args\n", ERROR));
	init_vars(&cub);
	mlx_get_screen_size(cub.cub_ptr \
		, &(cub.conf.win_max_w), &(cub.conf.win_max_h));
	if (get_conf(&cub, av[1]) == FALSE || check_map(&cub) == FALSE)
		return (free_cub(&cub, ERROR));
	cub_conf(&cub);
	if (!(initialize_window(&cub)) || setting_img(&cub) == FALSE \
		|| setting_window(&cub) == FALSE)
		exit_game(&cub, ERROR);
	if (check_sprite_info(&cub) == FALSE \
			|| (ac == 3 && create_bmp(&cub) == FALSE))
		exit_game(&cub, ERROR);
	mlx_hook(cub.win, X_EVENT_KEY_PRESS, 1L << 0, &key_press, &cub);
	mlx_hook(cub.win, 17, 1 << 17, &close_button_press, &cub);
	mlx_hook(cub.win, X_EVENT_KEY_RELEASE, 1L << 1, &key_release, &cub);
	mlx_loop_hook(cub.cub_ptr, &rendering_loop, &cub);
	mlx_loop(cub.cub_ptr);
}
