/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:16:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/01 20:29:19 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char const **av)
{
	void	*mlx_ptr;

	(void)ac;
	(void)av;
	mlx_ptr = mlx_init();
	mlx_new_window(mlx_ptr, 500, 500, "my win");
	return (0);
}
