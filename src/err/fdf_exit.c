/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:43:22 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 17:55:47 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_exit(t_vars *vars, int errno)
{
	if (vars->fdf->grid)
		free_2d((vars->fdf->grid), vars->fdf->grid_height);
	if (vars->fdf->v_grid)
		free_vertices((vars->fdf->v_grid), vars->fdf->grid_height);
	if (vars->fdf->v_grid_global)
		free_vertices((vars->fdf->v_grid_global), vars->fdf->grid_height);
	exit(errno);
}
