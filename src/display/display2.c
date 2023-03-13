/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dsiplay2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:11:36 by itan              #+#    #+#             */
/*   Updated: 2023/03/12 03:08:04 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_hue_right(t_fdf *fdf, int i, int j, int step)
{
	if (fdf->grid[i][j] >= fdf->grid[i][j + step])
		return ((double)fdf->grid[i][j] / (double)(fdf->max_height
				- fdf->min_height) * 24);
	else
		return ((double)fdf->grid[i][j + step] / (double)(fdf->max_height
				- fdf->min_height) * 24);
}

static int	get_hue_bot(t_fdf *fdf, int i, int j, int step)
{
	if (fdf->grid[i][j] >= fdf->grid[i + step][j])
		return ((double)fdf->grid[i][j] / (double)(fdf->max_height
				- fdf->min_height) * 24);
	else
		return ((double)fdf->grid[i + step][j] / (double)(fdf->max_height
				- fdf->min_height) * 24);
}

void	choose_node_to_draw(t_vars *var, int i, int j, int skip)
{
	t_fdf		*fdf;
	t_offset	start;
	t_offset	end1;
	t_offset	end2;

	fdf = var->fdf;
	start = perspective_projection(fdf->v_grid_global[i][j].v,
			fdf->focal_len, 25);
	if (j + skip < fdf->grid_width)
	{
		end1 = perspective_projection(fdf->v_grid_global[i][j + skip].v,
				fdf->focal_len, 25);
		plot_line(var, start, end1, get_hue_right(fdf, i, j, skip));
	}
	if (i + skip < fdf->grid_height)
	{
		end2 = perspective_projection(fdf->v_grid_global[i + skip][j].v,
				fdf->focal_len, 25);
		plot_line(var, start, end2, get_hue_bot(fdf, i, j, skip));
	}
}
