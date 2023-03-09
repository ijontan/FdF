/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:34:44 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 00:55:46 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_offset	perspective_projection(double v[3], double focal, double screen_p)
{
	t_offset	offset;
	double		dis_from_focal;

	dis_from_focal = screen_p - v[2] + focal;
	offset.x = (v[0] / dis_from_focal * focal) + 0.5;
	offset.y = (v[1] / dis_from_focal * focal) + 0.5;
	return (offset);
}
