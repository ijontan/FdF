/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:44:19 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 20:46:08 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	quaternion_rotate(t_quaternion *q, double v[3], double output[3])
{
	t_q_rot_var	var;

	if (output == NULL)
		return ;
	var.ww = q->w * q->w;
	var.xx = q->v[0] * q->v[0];
	var.yy = q->v[1] * q->v[1];
	var.zz = q->v[2] * q->v[2];
	var.wx = q->w * q->v[0];
	var.wy = q->w * q->v[1];
	var.wz = q->w * q->v[2];
	var.xy = q->v[0] * q->v[1];
	var.xz = q->v[0] * q->v[2];
	var.yz = q->v[1] * q->v[2];
	output[0] = var.ww * v[0] + 2 * var.wy * v[2] - 2 * var.wz * v[1] + var.xx
		* v[0] + 2 * var.xy * v[1] + 2 * var.xz * v[2] - var.zz * v[0] - var.yy
		* v[0];
	output[1] = 2 * var.xy * v[0] + var.yy * v[1] + 2 * var.yz * v[2] + 2
		* var.wz * v[0] - var.zz * v[1] + var.ww * v[1] - 2 * var.wx * v[2]
		- var.xx * v[1];
	output[2] = 2 * var.xz * v[0] + 2 * var.yz * v[1] + var.zz * v[2] - 2
		* var.wy * v[0] - var.yy * v[2] + 2 * var.wx * v[1] - var.xx * v[2]
		+ var.ww * v[2];
}

static void	quaternion_slerp_n(t_q_slerp_var *var, t_quaternion *result,
		double t)
{
	var->ratio_a = ft_sin((1 - t) * var->half_theta) / var->sin_half_theta;
	var->ratio_b = ft_sin(t * var->half_theta) / var->sin_half_theta;
	result->w = (var->q1->w * var->ratio_a + var->q2->w * var->ratio_b);
	result->v[0] = (var->q1->v[0] * var->ratio_a + var->q2->v[0]
			* var->ratio_b);
	result->v[1] = (var->q1->v[1] * var->ratio_a + var->q2->v[1]
			* var->ratio_b);
	result->v[2] = (var->q1->v[2] * var->ratio_a + var->q2->v[2]
			* var->ratio_b);
}

static int	quaternion_slerp_check_input(t_quaternion *q1, t_quaternion *q2,
		t_q_slerp_var *var, t_quaternion *output)
{
	if (ft_abs(var->cos_half_theta) >= 1.0)
	{
		*output = quaternion_dup(q1);
		return (1);
	}
	if (var->cos_half_theta < 0)
	{
		q2->w = -q2->w;
		q2->v[0] = -q2->v[0];
		q2->v[1] = -q2->v[1];
		q2->v[2] = -q2->v[2];
	}
	return (0);
}

void	quaternion_slerp(t_quaternion *q1, t_quaternion *q2, double t,
		t_quaternion *output)
{
	t_quaternion	result;
	t_q_slerp_var	var;

	var.q1 = q1;
	var.q2 = q2;
	var.cos_half_theta = q1->w * q2->w + q1->v[0] * q2->v[0] + q1->v[1]
		* q2->v[1] + q1->v[2] * q2->v[2];
	if (quaternion_slerp_check_input(q1, q2, &var, output))
		return ;
	var.half_theta = ft_acos(var.cos_half_theta);
	var.sin_half_theta = ft_sqrt(1.0 - var.cos_half_theta * var.cos_half_theta);
	if (ft_abs(var.sin_half_theta) < QUATERNION_EPS)
	{
		result.w = (q1->w * 0.5 + q2->w * 0.5);
		result.v[0] = (q1->v[0] * 0.5 + q2->v[0] * 0.5);
		result.v[1] = (q1->v[1] * 0.5 + q2->v[1] * 0.5);
		result.v[2] = (q1->v[2] * 0.5 + q2->v[2] * 0.5);
	}
	else
		quaternion_slerp_n(&var, &result, t);
	*output = result;
}
