/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:13 by itan              #+#    #+#             */
/*   Updated: 2023/03/09 03:04:22 by itan             ###   ########.fr       */
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
		image->buffer[pixel + 0] = (color >> 24);
		image->buffer[pixel + 1] = (color >> 16) & 0xFF;
		image->buffer[pixel + 2] = (color >> 8) & 0xFF;
		image->buffer[pixel + 3] = color & 0xFF;
	}
	else
	{
		image->buffer[pixel + 3] = (color >> 24);
		image->buffer[pixel + 2] = (color >> 16) & 0xFF;
		image->buffer[pixel + 1] = (color >> 8) & 0xFF;
		image->buffer[pixel + 0] = color & 0xFF;
	}
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
		{
			if (check_outofbound(isometric_projection(fdf->v_grid[i][j].v),
									var,
									20))
				continue ;
			if (fdf->v_grid[i][j].right)
				plot_line(var, isometric_projection(fdf->v_grid[i][j].v),
						isometric_projection(fdf->v_grid[i][j].right->v));
			if (fdf->v_grid[i][j].top)
				plot_line(var, isometric_projection(fdf->v_grid[i][j].v),
						isometric_projection(fdf->v_grid[i][j].top->v));
		}
	}
	mlx_put_image_to_window(var->mlx, var->win, image, 0, 0);
	mlx_destroy_image(var->mlx, image);
}
