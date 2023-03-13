/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:16:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 17:37:48 by itan             ###   ########.fr       */
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
	fdf->slerp_var.start_o = fdf->orientation;
	fdf->slerp_var.end_o = quaternion_create_id();
	fdf->slerp_var.out_o = quaternion_create_id();
}

static void	fdf_init(t_fdf *fdf)
{
	fdf->focal_len = 600;
	fdf->cycle_per_frame = 400;
	fdf->cycle_count = 0;
	fdf->slerp_var.t = 1.1;
	fdf->slerp_var.sign = 1;
	fdf->orientation = quaternion_create_id();
	fdf->global_position[0] = 0;
	fdf->global_position[1] = 0;
	fdf->global_position[2] = 0;
	fdf->hold.left_m = false;
	fdf->hold.right_m = false;
	fdf->hold.middle_m = false;
	fdf->image = NULL;
	fdf->grid = NULL;
	fdf->v_grid = NULL;
	fdf->v_grid_global = NULL;
}

int	main(int ac, char const **av)
{
	t_vars	vars;
	t_fdf	fdf;

	ft_printf("%s", "\033[H\033[2J");
	ft_printf("%sfdf!!%s\n", "\033[1;32m", "\033[0m");
	// int		i;
	vars.win_h = 1000;
	vars.win_w = 1000;
	vars.fdf = &fdf;
	if (ac != 2)
		return (1);
	fdf_init(&fdf);
	// i = -1;
	// while (++i < 25)
	// 	ft_printf("%x, ", hue_to_int(i, 1));
	parse_map((char *)(av[1]), vars.fdf);
	// print_map(fdf);
	create_vertices(vars.fdf);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.win_w, vars.win_h, "my win");
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 4, 0, mouse_hook_down, &vars);
	mlx_hook(vars.win, 5, 0, mouse_hook_up, &vars);
	mlx_hook(vars.win, 6, 0, mouse_move_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop_hook(vars.mlx, loop_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook_down, &vars);
	// mlx_key_hook(vars.win, key_hook, &vars);
	set_isomatric(&fdf);
	display(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
