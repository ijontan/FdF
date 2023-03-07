/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:52:39 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 11:47:11 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	quaternion_from_axis_angle(double axis[3], double angle,
		t_quaternion *output)
{
	double	c;

	if (output == NULL)
		return ;
	output->w = ft_cos(angle / 2.0);
	c = ft_sin(angle / 2.0);
	output->v[0] = c * axis[0];
	output->v[1] = c * axis[1];
	output->v[2] = c * axis[2];
}

double	quaternion_to_axis_angle(t_quaternion *q, double output[3])
{
	double	angle;
	double	multiplier;

	if (output == NULL)
		return (0.0);
	angle = 2.0 * ft_acos(q->w);
	multiplier = ft_q_in_sqrt(1.0 - q->w * q->w);
	if (multiplier > 10000000000.0)
	{
		output[0] = q->v[0] * multiplier;
		output[1] = q->v[1] * multiplier;
		output[2] = q->v[2] * multiplier;
	}
	else
	{
		output[0] = 1;
		output[1] = 0;
		output[2] = 0;
	}
	return (angle);
}

void	quaternion_x_rotation(double angle, t_quaternion *output)
{
	double	axis[3];

	if (output == NULL)
		return ;
	axis[0] = 1.0;
	axis[1] = 0.0;
	axis[2] = 0.0;
	quaternion_from_axis_angle(axis, angle, output);
}

void	quaternion_y_rotation(double angle, t_quaternion *output)
{
	double	axis[3];

	if (output == NULL)
		return ;
	axis[0] = 0.0;
	axis[1] = 1.0;
	axis[2] = 0.0;
	quaternion_from_axis_angle(axis, angle, output);
}

void	quaternion_z_rotation(double angle, t_quaternion *output)
{
	double	axis[3];

	if (output == NULL)
		return ;
	axis[0] = 0.0;
	axis[1] = 0.0;
	axis[2] = 1.0;
	quaternion_from_axis_angle(axis, angle, output);
}
