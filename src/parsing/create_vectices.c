/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vectices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:12:40 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 06:14:40 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_vertex(t_vertex *vertex)
{
	vertex->top = NULL;
	vertex->bot = NULL;
	vertex->left = NULL;
	vertex->right = NULL;
}

static void	assign_vertices(t_fdf *fdf, t_vertex **v_grid)
{
	int	i;
	int	j;

	fdf->line_dis_2 = 1 + 2000 / (fdf->grid_height * fdf->grid_width);
	fdf->value_weight = 1;
	i = 0;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			if ((fdf->grid)[i][j] > fdf->max_height)
				fdf->max_height = (fdf->grid)[i][j];
			if ((fdf->grid)[i][j] < fdf->min_height)
				fdf->min_height = (fdf->grid)[i][j];
			v_grid[i][j].v[1] = (double)(i - fdf->grid_height / 2) * 2
				* fdf->line_dis_2 + fdf->line_dis_2;
			v_grid[i][j].v[0] = (double)(j - fdf->grid_width / 2) * 2
				* fdf->line_dis_2 + fdf->line_dis_2;
			v_grid[i][j].v[2] = (double)((fdf->grid)[i][j]);
			init_vertex(&(v_grid[i][j]));
			j++;
		}
		i++;
	}
}

static void	link_vertices(t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->grid_height)
	{
		j = -1;
		while (++j < fdf->grid_width)
		{
			init_vertex(&(fdf->v_grid_global[i][j]));
			if (i != 0)
				fdf->v_grid_global[i][j].top = &(fdf->v_grid_global[i - 1][j]);
			if (j != 0)
				fdf->v_grid_global[i][j].left = &(fdf->v_grid_global[i][j - 1]);
			if (i != fdf->grid_height - 1)
				fdf->v_grid_global[i][j].bot = &(fdf->v_grid_global[i + 1][j]);
			if (j != fdf->grid_width - 1)
				fdf->v_grid_global[i][j].right = &(fdf->v_grid_global[i][j
						+ 1]);
		}
	}
}

void	create_vertices(t_fdf *fdf)
{
	t_vertex	**v_grid;
	t_vertex	**v_grid_global;
	int			i;

	fdf->max_height = -2147483648;
	fdf->min_height = +2147483647;
	i = 0;
	v_grid = ft_calloc(fdf->grid_height, sizeof(t_vertex *));
	while (i < fdf->grid_height)
		v_grid[i++] = ft_calloc(fdf->grid_width, sizeof(t_vertex));
	i = 0;
	v_grid_global = ft_calloc(fdf->grid_height, sizeof(t_vertex *));
	while (i < fdf->grid_height)
		v_grid_global[i++] = ft_calloc(fdf->grid_width, sizeof(t_vertex));
	fdf->v_grid = v_grid;
	fdf->v_grid_global = v_grid_global;
	assign_vertices(fdf, v_grid);
	link_vertices(fdf);
	ft_printf("max:%i, min:%i\n", fdf->max_height, fdf->min_height);
}
