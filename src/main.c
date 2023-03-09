/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:16:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/09 21:00:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	apply_rotation(t_fdf *fdf)
{
	int				i;
	int				j;
	t_quaternion	q1;
	t_quaternion	q2;
	double			tmp_v[3];

	tmp_v[0] = 1;
	tmp_v[1] = 1;
	tmp_v[2] = 0;
	quaternion_z_rotation(0, &q1);
	quaternion_from_axis_angle(tmp_v, PI + PI_2, &q2);
	// quaternion_x_rotation(-PI_4, &q1);
	// quaternion_x_rotation(0, &q1);
	// quaternion_z_rotation(0, &q2);
	i = 0;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			quaternion_rotate(&q1, fdf->v_grid[i][j].v, tmp_v);
			quaternion_rotate(&q2, tmp_v, fdf->v_grid[i][j].v);
			j++;
		}
		i++;
	}
}

int	main(int ac, char const **av)
{
	t_vars	vars;
	t_fdf	fdf;

	// int		i;
	vars.win_h = 1000;
	vars.win_w = 1000;
	vars.fdf = &fdf;
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
	// mlx_hook(vars.win, 2, 0, mouse_hook, &vars);
	mlx_hook(vars.win, 4, 0, mouse_hook, &vars);
	mlx_hook(vars.win, 6, 0, mouse_move_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	apply_rotation(vars.fdf);
	display(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
