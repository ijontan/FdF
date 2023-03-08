/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vectices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:12:40 by itan              #+#    #+#             */
/*   Updated: 2023/03/09 04:49:25 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	assign_vertices(t_fdf *fdf, t_vertex **v_grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			v_grid[i][j].v[0] = (double)(i - fdf->grid_width / 2) * 2 + 1;
			v_grid[i][j].v[1] = (double)(j - fdf->grid_height / 2) * 2 + 1;
			v_grid[i][j].v[2] = (double)((fdf->grid)[i][j]);
			v_grid[i][j].top = NULL;
			v_grid[i][j].bot = NULL;
			v_grid[i][j].left = NULL;
			v_grid[i][j].right = NULL;
			j++;
		}
		i++;
	}
}

static void	link_vertices(t_fdf *fdf, t_vertex **v_grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			if (i != 0)
				v_grid[i][j].top = &(v_grid[i - 1][j]);
			if (j != 0)
				v_grid[i][j].left = &(v_grid[i][j - 1]);
			if (i != fdf->grid_height - 1)
				v_grid[i][j].bot = &(v_grid[i + 1][j]);
			if (j != fdf->grid_width - 1)
				v_grid[i][j].right = &(v_grid[i][j + 1]);
			j++;
		}
		i++;
	}
}

void	create_vertices(t_fdf *fdf)
{
	t_vertex	**v_grid;
	int			i;

	i = 0;
	v_grid = ft_calloc(fdf->grid_height, sizeof(t_vertex *));
	while (i < fdf->grid_height)
		v_grid[i++] = ft_calloc(fdf->grid_width, sizeof(t_vertex));
	assign_vertices(fdf, v_grid);
	link_vertices(fdf, v_grid);
	fdf->v_grid = v_grid;
}
