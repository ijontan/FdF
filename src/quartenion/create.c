/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 01:16:23 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 11:03:08 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_quaternion	quaternion_create(double w, double v0, double v1, double v2)
{
	t_quaternion	q;

	q.w = w;
	q.v[0] = v0;
	q.v[1] = v1;
	q.v[2] = v2;
	return (q);
}

t_quaternion	quaternion_create_id(void)
{
	return (quaternion_create(1, 0, 0, 0));
}

t_quaternion	quaternion_dup(t_quaternion *q)
{
	return (quaternion_create(q->w, q->v[0], q->v[1], q->v[2]));
}
