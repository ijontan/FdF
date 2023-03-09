/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:16:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 06:46:44 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_isomatric(t_fdf *fdf)
{
	t_quaternion	q1;

	quaternion_z_rotation(-PI_4, &q1);
	quaternion_multiply(&q1, &fdf->orientation, &fdf->orientation);
	quaternion_x_rotation(-PI_4, &q1);
	quaternion_multiply(&q1, &fdf->orientation, &fdf->orientation);
}

int	main(int ac, char const **av)
{
	t_vars	vars;
	t_fdf	fdf;

	// int		i;
	vars.win_h = 500;
	vars.win_w = 500;
	vars.fdf = &fdf;
	fdf.focal_len = 600;
	if (ac != 2)
		return (1);
	// i = -1;
	// while (++i < 25)
	// 	ft_printf("%x, ", hue_to_int(i, 1));
	parse_map((char *)(av[1]), vars.fdf);
	// print_map(fdf);
	create_vertices(vars.fdf);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.win_w, vars.win_h, "my win");
	// mlx_hook(vars.win, 2, 0, key_hook, &vars);
	// mlx_hook(vars.win, 4, 0, mouse_hook_down, &vars);
	fdf.orientation = quaternion_create_id();
	mlx_hook(vars.win, 6, 0, mouse_move_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook_down, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	set_isomatric(&fdf);
	// apply_rotation(vars.fdf);
	display(&vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
