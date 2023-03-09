/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:13 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 04:19:24 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static bool	check_outofbound(t_offset offset, t_vars *var, int border)
{
	if (offset.x >= var->win_w / 2 + border || offset.x <= -var->win_w / 2
		- border || offset.y >= var->win_h / 2 + border || offset.y <=
		-var->win_h / 2 - border)
		return (true);
	return (false);
}

void	add_pixel(t_offset offset, t_vars *var, int color)
{
	int		pixel;
	t_image	*image;

	image = var->fdf->image;
	if (check_outofbound(offset, var, 0))
		return ;
	pixel = ((offset.y + var->win_h / 2) * image->line_bytes) + ((offset.x
				+ var->win_w / 2) * image->pixel_bits / 8);
	if (image->endian == 1)
	{
		image->buffer[pixel + 0] += (color >> 24);
		image->buffer[pixel + 1] += (color >> 16) & 0xFF;
		image->buffer[pixel + 2] += (color >> 8) & 0xFF;
		image->buffer[pixel + 3] += color & 0xFF;
	}
	else
	{
		image->buffer[pixel + 3] += (color >> 24);
		image->buffer[pixel + 2] += (color >> 16) & 0xFF;
		image->buffer[pixel + 1] += (color >> 8) & 0xFF;
		image->buffer[pixel + 0] += color & 0xFF;
	}
}

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

void	display(t_vars *var)
{
	int		i;
	int		j;
	void	*image;
	t_fdf	*fdf;
	t_image	*image_v;

	fdf = var->fdf;
	fdf->image = malloc(sizeof(t_image));
	image_v = fdf->image;
	image = mlx_new_image(var->mlx, var->win_w, var->win_h);
	image_v->buffer = mlx_get_data_addr(image, &(image_v->pixel_bits),
			&(image_v->line_bytes), &(image_v->endian));
	if (!image_v->buffer)
		return ;
	i = -1;
	while (++i < fdf->grid_height)
	{
		j = -1;
		while (++j < fdf->grid_width)
			quaternion_rotate(&(fdf->orientation), fdf->v_grid[i][j].v,
					fdf->v_grid_global[i][j].v);
	}
	i = -1;
	while (++i < fdf->grid_height)
	{
		j = -1;
		while (++j < fdf->grid_width)
		{
			// if (check_outofbound(orthographic_projection(fdf->v_grid[i][j].v),
			// 						var,
			// 						20))
			// 	continue ;
			// if (fdf->v_grid[i][j].right)
			// 	plot_line(var, orthographic_projection(fdf->v_grid[i][j].v),
			// 			orthographic_projection(fdf->v_grid[i][j].right->v));
			// if (fdf->v_grid[i][j].top)
			// 	plot_line(var, orthographic_projection(fdf->v_grid[i][j].v),
			// 			orthographic_projection(fdf->v_grid[i][j].top->v));
			if (check_outofbound(perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
									var,
									fdf->line_dis_2 * 2))
				continue ;
			if (fdf->v_grid_global[i][j].v[2] > 600)
				continue ;
			if (fdf->line_dis_2 * 2 < 0.5)
			{
				if (fdf->v_grid_global[i][j].right && fdf->v_grid_global[i][j
					+ 1].right && fdf->v_grid_global[i][j + 2].right
					&& fdf->v_grid_global[i][j + 3].right)
					plot_line(var,
								perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
								perspective_projection(fdf->v_grid_global[i][j
										+ 4].v, 600, 25),
								get_hue_right(fdf, i, j, 4));
				if (fdf->v_grid_global[i][j].bot && fdf->v_grid_global[i
					+ 1][j].bot && fdf->v_grid_global[i + 2][j].bot
					&& fdf->v_grid_global[i + 3][j].bot)
					plot_line(var,
								perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
								perspective_projection(fdf->v_grid_global[i
										+ 4][j].v, 600, 25),
								get_hue_bot(fdf, i, j, 4));
				j += 3;
			}
			if (fdf->line_dis_2 * 2 < 2)
			{
				if (fdf->v_grid_global[i][j].right && fdf->v_grid_global[i][j
					+ 1].right)
					plot_line(var,
								perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
								perspective_projection(fdf->v_grid_global[i][j
										+ 2].v, 600, 25),
								get_hue_right(fdf, i, j, 2));
				if (fdf->v_grid_global[i][j].bot && fdf->v_grid_global[i
					+ 1][j].bot)
					plot_line(var,
								perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
								perspective_projection(fdf->v_grid_global[i
										+ 2][j].v, 600, 25),
								get_hue_bot(fdf, i, j, 2));
				j++;
			}
			else
			{
				if (fdf->v_grid_global[i][j].right)
					plot_line(var,
								perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
								perspective_projection(fdf->v_grid_global[i][j
										+ 1].v, 600, 25),
								get_hue_right(fdf, i, j, 1));
				if (fdf->v_grid_global[i][j].bot)
					plot_line(var,
								perspective_projection(fdf->v_grid_global[i][j].v,
														600,
														25),
								perspective_projection(fdf->v_grid_global[i
										+ 1][j].v, 600, 25),
								get_hue_bot(fdf, i, j, 1));
			}
		}
	}
	mlx_clear_window(var->mlx, var->win);
	mlx_put_image_to_window(var->mlx, var->win, image, 0, 0);
	mlx_destroy_image(var->mlx, image);
}
