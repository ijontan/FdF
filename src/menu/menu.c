/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:34:36 by itan              #+#    #+#             */
/*   Updated: 2023/03/27 04:49:40 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_menu(t_vars *var)
{
	char	*str;
	char	*val;

	mlx_string_put(var->mlx, var->win, 100, var->win_h - 200, 0xffbbbbbb,
			"FDF");
	val = ft_itoa(var->fdf->value_weight);
	str = ft_strjoin("height weight( q/a ): ", val);
	mlx_string_put(var->mlx, var->win, 100, var->win_h - 180, 0xffbbbbbb, str);
	free(val);
	free(str);
	val = ft_itoa(var->fdf->base_hue);
	str = ft_strjoin("base hue( r/f ): ", val);
	mlx_string_put(var->mlx, var->win, 100, var->win_h - 160,
			hue_to_int(var->fdf->base_hue, 0xFF), str);
	free(val);
	free(str);
	val = ft_itoa(var->fdf->hue_range);
	str = ft_strjoin("hue range( t/g ): ", val);
	mlx_string_put(var->mlx, var->win, 100, var->win_h - 140,
			hue_to_int(var->fdf->base_hue + var->fdf->hue_range, 0xFF), str);
	free(val);
	free(str);
	val = ft_itoa(var->fdf->focal_len);
	str = ft_strjoin("focal length( e/d ): ", val);
	mlx_string_put(var->mlx, var->win, 100, var->win_h - 120, 0xffbbbbbb, str);
	free(val);
	free(str);
}
