/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:11:36 by itan              #+#    #+#             */
/*   Updated: 2023/03/27 03:10:45 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_hue_right(t_fdf *fdf, int i, int j, int step)
{
	double	ratio;

	if (fdf->grid[i][j] >= fdf->grid[i][j + step])
		ratio = (double)fdf->grid[i][j] / (double)(fdf->max_height
				- fdf->min_height);
	else
		ratio = (double)fdf->grid[i][j + step] / (double)(fdf->max_height
				- fdf->min_height);
	return (fdf->base_hue + ratio * fdf->hue_range);
}

static int	get_hue_bot(t_fdf *fdf, int i, int j, int step)
{
	double	ratio;

	if (fdf->grid[i][j] >= fdf->grid[i + step][j])
		ratio = (double)fdf->grid[i][j] / (double)(fdf->max_height
				- fdf->min_height);
	else
		ratio = (double)fdf->grid[i + step][j] / (double)(fdf->max_height
				- fdf->min_height);
	return (fdf->base_hue + ratio * fdf->hue_range);
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

void	set_all_black(t_vars *var)
{
	int		pixel;
	int		i;
	int		j;
	t_image	*image;

	image = var->fdf->image;
	i = -1;
	while (++i < var->win_h)
	{
		j = -1;
		while (++j < var->win_w)
		{
			pixel = (i * image->line_bytes) + (j * image->pixel_bits / 8);
			if (image->endian == 1)
				image->buffer[pixel + 0] = 0xff;
			else
				image->buffer[pixel + 3] = 0xff;
		}
	}
}
