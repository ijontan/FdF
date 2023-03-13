/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:16:20 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 19:04:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	animate_to_view(int keycode, t_vars *vars)
{
	if (keycode == 18)
		animate_to_iso(vars);
	if (keycode == 19)
		animate_to_perspec(vars);
	if (keycode == 20)
		animate_to_top(vars);
}

static void	arrow_keys_translate(int keycode, t_vars *vars)
{
	if (keycode == 123)
	{
		translate(vars->fdf->global_position, -10, 0, 0);
		display(vars);
	}
	if (keycode == 124)
	{
		translate(vars->fdf->global_position, 10, 0, 0);
		display(vars);
	}
	if (keycode == 125)
	{
		translate(vars->fdf->global_position, 0, 10, 0);
		display(vars);
	}
	if (keycode == 126)
	{
		translate(vars->fdf->global_position, 0, -10, 0);
		display(vars);
	}
}

static void	other_func(int keycode, t_vars *vars)
{
	if (keycode == 14 && vars->fdf->focal_len < 209715200)
		vars->fdf->focal_len = (vars->fdf->focal_len - 130) * 2;
	else if (keycode == 2 && vars->fdf->focal_len >= 130)
		vars->fdf->focal_len = vars->fdf->focal_len / 2 + 130;
	else if (keycode == 0)
		vars->fdf->value_weight -= 0.1;
	else if (keycode == 12)
		vars->fdf->value_weight += 0.1;
	else if (keycode == 1)
	{
		vars->fdf->scale *= 0.9;
		vars->fdf->line_dis_2 *= 0.9;
	}
	else if (keycode == 13)
	{
		vars->fdf->scale *= 1.0 / 0.9;
		vars->fdf->line_dis_2 *= 1.0 / 0.9;
	}
	else
		return ;
	display(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	animate_to_view(keycode, vars);
	arrow_keys_translate(keycode, vars);
	other_func(keycode, vars);
	return (0);
}
