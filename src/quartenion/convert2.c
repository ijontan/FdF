/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:06:39 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 11:42:11 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_e_convert_var
{
	double	cy;
	double	sy;
	double	cr;
	double	sr;
	double	cp;
	double	sp;
}			t_e_convert_var;

void	quaternion_from_euler3(double euler[3], t_quaternion *output)
{
	t_e_convert_var	var;

	if (output == NULL)
		return ;
	var.cy = ft_cos(euler[2] * 0.5);
	var.sy = ft_sin(euler[2] * 0.5);
	var.cr = ft_cos(euler[0] * 0.5);
	var.sr = ft_sin(euler[0] * 0.5);
	var.cp = ft_cos(euler[1] * 0.5);
	var.sp = ft_sin(euler[1] * 0.5);
	output->w = var.cy * var.cr * var.cp + var.sy * var.sr * var.sp;
	output->v[0] = var.cy * var.sr * var.cp - var.sy * var.cr * var.sp;
	output->v[1] = var.cy * var.cr * var.sp + var.sy * var.sr * var.cp;
	output->v[2] = var.sy * var.cr * var.cp - var.cy * var.sr * var.sp;
}

void	quaternion_to_euler3(t_quaternion *q, double output[3])
{
	double	sinr_cosp;
	double	cosr_cosp;
	double	sinp;
	double	siny_cosp;
	double	cosy_cosp;

	if (output == NULL)
		return ;
	sinr_cosp = +2.0 * (q->w * q->v[0] + q->v[1] * q->v[2]);
	cosr_cosp = +1.0 - 2.0 * (q->v[0] * q->v[0] + q->v[1] * q->v[1]);
	output[0] = ft_atan2(sinr_cosp, cosr_cosp);
	sinp = +2.0 * (q->w * q->v[1] - q->v[2] * q->v[0]);
	if (ft_abs(sinp) >= 1)
		output[1] = ft_copysign(PI_2, sinp);
	else
		output[1] = ft_asin(sinp);
	siny_cosp = +2.0 * (q->w * q->v[2] + q->v[0] * q->v[1]);
	cosy_cosp = +1.0 - 2.0 * (q->v[1] * q->v[1] + q->v[2] * q->v[2]);
	output[2] = ft_atan2(siny_cosp, cosy_cosp);
}

void	quaternion_conjugate(t_quaternion *q, t_quaternion *output)
{
	if (output == NULL)
		return ;
	output->w = q->w;
	output->v[0] = -q->v[0];
	output->v[1] = -q->v[1];
	output->v[2] = -q->v[2];
}
