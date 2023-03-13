/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:00:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/14 00:10:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	animate_to_iso(t_vars *vars)
{
	t_quaternion	q1;

	vars->fdf->slerp_var.start_o = vars->fdf->orientation;
	vars->fdf->slerp_var.end_o = quaternion_create_id();
	quaternion_z_rotation(-PI_4, &q1);
	quaternion_multiply(&q1, &vars->fdf->slerp_var.end_o,
		&vars->fdf->slerp_var.end_o);
	quaternion_x_rotation(-PI_4, &q1);
	quaternion_multiply(&q1, &vars->fdf->slerp_var.end_o,
		&vars->fdf->slerp_var.end_o);
	vars->fdf->slerp_var.t = 0.0;
	vars->fdf->slerp_var.sign = 1;
	vars->fdf->orientation = vars->fdf->slerp_var.end_o;
	ft_printf("%sanimating to isomatric projection...%s\n",
		"\033[1;36m", "\033[0m");
}

void	animate_to_perspec(t_vars *vars)
{
	vars->fdf->slerp_var.start_o = vars->fdf->orientation;
	vars->fdf->slerp_var.end_o = vars->fdf->orientation;
	vars->fdf->slerp_var.out_o = vars->fdf->orientation;
	vars->fdf->slerp_var.t = 0.0;
	vars->fdf->slerp_var.sign = -1;
	vars->fdf->orientation = vars->fdf->slerp_var.end_o;
	ft_printf("%sanimating to perspective projection...%s\n",
		"\033[1;36m", "\033[0m");
}

void	animate_to_top(t_vars *vars)
{
	vars->fdf->slerp_var.start_o = vars->fdf->orientation;
	vars->fdf->slerp_var.end_o = quaternion_create_id();
	vars->fdf->slerp_var.t = 0.0;
	vars->fdf->slerp_var.sign = 1;
	vars->fdf->orientation = vars->fdf->slerp_var.end_o;
	ft_printf("%sanimating to top view...%s\n", "\033[1;36m", "\033[0m");
}
