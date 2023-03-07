/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:16:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/03 13:01:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char const **av)
{
	t_vars	vars;
	t_fdf	fdf;

	if (ac != 2)
		return (1);
	parse_map((char *)(av[1]), &fdf);
	print_map(&fdf);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500, 500, "my win");
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_mouse_hook(vars.win, &mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
