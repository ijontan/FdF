/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:13 by itan              #+#    #+#             */
/*   Updated: 2023/03/08 05:14:49 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_pixel(t_offset offset, t_vars *var, t_fdf *fdf, int color)
{
	int	pixel;

	if (offset.x >= var->win_w / 2 || offset.x <= -var->win_w / 2
		|| offset.y >= var->win_h / 2 || offset.y <= -var->win_h / 2)
		return ;
	pixel = ((offset.y + var->win_h / 2) * fdf->line_bytes) + ((offset.x
				+ var->win_w / 2) * fdf->pixel_bits / 8);
	if (fdf->endian == 1)
	{
		fdf->buffer[pixel + 0] = (color >> 24);
		fdf->buffer[pixel + 1] = (color >> 16) & 0xFF;
		fdf->buffer[pixel + 2] = (color >> 8) & 0xFF;
		fdf->buffer[pixel + 3] = color & 0xFF;
	}
	else
	{
		fdf->buffer[pixel + 3] = (color >> 24);
		fdf->buffer[pixel + 2] = (color >> 16) & 0xFF;
		fdf->buffer[pixel + 1] = (color >> 8) & 0xFF;
		fdf->buffer[pixel + 0] = color & 0xFF;
	}
}

void	display(t_vars *var, t_fdf *fdf)
{
	int		i;
	int		j;
	void	*image;

	image = mlx_new_image(var->mlx, var->win_w, var->win_h);
	i = 0;
	fdf->buffer = mlx_get_data_addr(image, &(fdf->pixel_bits),
			&(fdf->line_bytes), &(fdf->endian));
	ft_printf("\n%i\n", fdf->pixel_bits);
	if (!fdf->buffer)
		return ;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			if (fdf->v_grid[i][j].right)
				plot_line(var, fdf, isometric_projection(fdf->v_grid[i][j].v),
						isometric_projection(fdf->v_grid[i][j].right->v));
			if (fdf->v_grid[i][j].top)
				plot_line(var, fdf, isometric_projection(fdf->v_grid[i][j].v),
						isometric_projection(fdf->v_grid[i][j].top->v));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(var->mlx, var->win, image, 0, 0);
	mlx_destroy_image(var->mlx, image);
}
