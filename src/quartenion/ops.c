/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:47:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 11:43:09 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	quaternion_equal(t_quaternion *q1, t_quaternion *q2)
{
	bool	equal_w;
	bool	equal_v0;
	bool	equal_v1;
	bool	equal_v2;

	equal_w = ft_abs(q1->w - q2->w) <= QUATERNION_EPS;
	equal_v0 = ft_abs(q1->v[0] - q2->v[0]) <= QUATERNION_EPS;
	equal_v1 = ft_abs(q1->v[1] - q2->v[1]) <= QUATERNION_EPS;
	equal_v2 = ft_abs(q1->v[2] - q2->v[2]) <= QUATERNION_EPS;
	return (equal_w && equal_v0 && equal_v1 && equal_v2);
}

// void	quaternion_print(t_quaternion *q)
// {
// 	fprintf(file, "(%.3f, %.3f, %.3f, %.3f)", q->w, q->v[0], q->v[1], q->v[2]);
// }

double	quaternion_norm(t_quaternion *q)
{
	if (q == NULL)
		return (0);
	return (ft_sqrt(q->w * q->w + q->v[0] * q->v[0] + q->v[1] * q->v[1]
			+ q->v[2] * q->v[2]));
}

void	quaternion_normalize(t_quaternion *q, t_quaternion *output)
{
	double	len;

	if (output == NULL)
		return ;
	len = quaternion_norm(q);
	*output = quaternion_create(q->w / len, q->v[0] / len, q->v[1] / len,
			q->v[2] / len);
}

void	quaternion_multiply(t_quaternion *q1, t_quaternion *q2,
		t_quaternion *output)
{
	t_quaternion	result;

	if (output == NULL)
		return ;
	result.w = q1->w * q2->w - q1->v[0] * q2->v[0] - q1->v[1] * q2->v[1]
		- q1->v[2] * q2->v[2];
	result.v[0] = q1->v[0] * q2->w + q1->w * q2->v[0] + q1->v[1] * q2->v[2]
		- q1->v[2] * q2->v[1];
	result.v[1] = q1->w * q2->v[1] - q1->v[0] * q2->v[2] + q1->v[1] * q2->w
		+ q1->v[2] * q2->v[0];
	result.v[2] = q1->w * q2->v[2] + q1->v[0] * q2->v[1] - q1->v[1] * q2->v[0]
		+ q1->v[2] * q2->w;
	*output = result;
}
