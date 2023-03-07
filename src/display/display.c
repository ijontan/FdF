/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:13 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 21:23:39 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display(t_vars *var, t_fdf *fdf)
{
	int			i;
	int			j;
	int			pixel;
	t_offset	offset;
	void		*image;

	image = mlx_new_image(var->mlx, var->win_w, var->win_h);
	i = 0;
	fdf->buffer = mlx_get_data_addr(image, &(fdf->pixel_bits),
			&(fdf->line_bytes), &(fdf->endian));
	if (!fdf->buffer)
		return ;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
		{
			offset = isometric_projection(fdf->v_grid[i][j].v);
			if (offset.x >= var->win_w / 2 || offset.x <= -var->win_w / 2
				|| offset.y >= var->win_h / 2 || offset.y <= -var->win_h / 2)
			{
				j++;
				continue ;
			}
			pixel = ((offset.y + var->win_h / 2) * fdf->line_bytes) + ((offset.x
						+ var->win_w / 2) * 4);
			fdf->buffer[pixel + 0] = (char)0xFF;
			fdf->buffer[pixel + 1] = (char)0xFF;
			fdf->buffer[pixel + 2] = (char)0xFF;
			fdf->buffer[pixel + 3] = (char)0xFF;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(var->mlx, var->win, image, 0, 0);
	mlx_destroy_image(var->mlx, image);
}
