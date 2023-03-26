/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:16:13 by itan              #+#    #+#             */
/*   Updated: 2023/03/27 04:49:17 by itan             ###   ########.fr       */
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

void	apply_rotation_and_translation(t_fdf *fdf)
{
	int		i;
	int		j;
	double	tmp_v[3];

	i = -1;
	while (++i < fdf->grid_height)
	{
		j = -1;
		while (++j < fdf->grid_width)
		{
			tmp_v[0] = fdf->v_grid[i][j].v[0];
			tmp_v[1] = fdf->v_grid[i][j].v[1];
			tmp_v[2] = fdf->v_grid[i][j].v[2] * fdf->value_weight;
			if (fdf->slerp_var.t < 1)
				quaternion_rotate(&(fdf->slerp_var.out_o), tmp_v,
						fdf->v_grid_global[i][j].v);
			else
				quaternion_rotate(&(fdf->orientation), tmp_v,
						fdf->v_grid_global[i][j].v);
			translate(fdf->v_grid_global[i][j].v, fdf->global_position[0]
					/ fdf->scale, fdf->global_position[1] / fdf->scale,
					fdf->global_position[2] / fdf->scale);
			scale(fdf->v_grid_global[i][j].v, fdf->scale);
		}
	}
}

static void	iterate_vertices(t_vars *var, t_fdf *fdf)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fdf->grid_height)
	{
		j = -1;
		while (++j < fdf->grid_width)
		{
			if (check_outofbound(
					perspective_projection(fdf->v_grid_global[i][j].v,
											fdf->focal_len,
											25),
					var,
					fdf->line_dis_2 * 4))
				continue ;
			if (fdf->v_grid_global[i][j].v[2] > fdf->focal_len)
				continue ;
			choose_node_to_draw(var, i, j, fdf->skip);
			j += fdf->skip - 1;
		}
		i += fdf->skip - 1;
	}
}

void	display(t_vars *var)
{
	void	*image;
	t_fdf	*fdf;
	t_image	image_v;

	fdf = var->fdf;
	fdf->image = &image_v;
	image = mlx_new_image(var->mlx, var->win_w, var->win_h);
	image_v.buffer = mlx_get_data_addr(image, &(image_v.pixel_bits),
			&(image_v.line_bytes), &(image_v.endian));
	if (!image_v.buffer)
		return ;
	fdf->skip = 1 / (fdf->line_dis_2 * 0.9) + 1;
	set_all_black(var);
	apply_rotation_and_translation(fdf);
	iterate_vertices(var, fdf);
	mlx_clear_window(var->mlx, var->win);
	mlx_put_image_to_window(var->mlx, var->win, image, 0, 0);
	display_menu(var);
	mlx_destroy_image(var->mlx, image);
}
