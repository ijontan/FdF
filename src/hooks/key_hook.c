/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:16:20 by itan              #+#    #+#             */
/*   Updated: 2023/03/27 03:15:07 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	animate_to_view(int keycode, t_vars *vars)
{
	if (keycode == KEY_1)
		animate_to_iso(vars);
	if (keycode == KEY_2)
		animate_to_perspec(vars);
	if (keycode == KEY_3)
		animate_to_top(vars);
}

static void	arrow_keys_translate(int keycode, t_vars *vars)
{
	if (keycode == KEY_LEFT)
	{
		translate(vars->fdf->global_position, -10, 0, 0);
		display(vars);
	}
	if (keycode == KEY_RIGHT)
	{
		translate(vars->fdf->global_position, 10, 0, 0);
		display(vars);
	}
	if (keycode == KEY_DOWN)
	{
		translate(vars->fdf->global_position, 0, 10, 0);
		display(vars);
	}
	if (keycode == KEY_UP)
	{
		translate(vars->fdf->global_position, 0, -10, 0);
		display(vars);
	}
}

static void	other_func(int keycode, t_vars *vars)
{
	if (keycode == KEY_E && vars->fdf->focal_len < 209715200)
		vars->fdf->focal_len = (vars->fdf->focal_len - 130) * 2;
	else if (keycode == KEY_D && vars->fdf->focal_len >= 130)
		vars->fdf->focal_len = vars->fdf->focal_len / 2 + 130;
	else if (keycode == KEY_A)
		vars->fdf->value_weight -= 0.1;
	else if (keycode == KEY_Q)
		vars->fdf->value_weight += 0.1;
	else if (keycode == KEY_S)
	{
		vars->fdf->scale *= 0.9;
		vars->fdf->line_dis_2 *= 0.9;
	}
	else if (keycode == KEY_W)
	{
		vars->fdf->scale *= 1.0 / 0.9;
		vars->fdf->line_dis_2 *= 1.0 / 0.9;
	}
	else
		return ;
	display(vars);
}

static void	hue_manip(int keycode, t_vars *vars)
{
	if (keycode == KEY_R)
		vars->fdf->base_hue += 10;
	else if (keycode == KEY_F)
		vars->fdf->base_hue -= 10;
	else if (keycode == KEY_T)
		vars->fdf->hue_range += 10;
	else if (keycode == KEY_G)
		vars->fdf->hue_range -= 10;
	else
		return ;
	display(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	animate_to_view(keycode, vars);
	arrow_keys_translate(keycode, vars);
	other_func(keycode, vars);
	hue_manip(keycode, vars);
	if (keycode == KEY_ESC)
	{
		ft_printf("%sexiting the program%s\n", "\033[1;33m", "\033[0m");
		fdf_exit(vars, 0);
	}
	return (0);
}
