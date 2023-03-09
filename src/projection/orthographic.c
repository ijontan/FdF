/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orthographic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:08:06 by itan              #+#    #+#             */
/*   Updated: 2023/03/09 14:39:43 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_offset	orthographic_projection(double v[3])
{
	t_offset	offset;

	offset.x = (int)v[0];
	offset.y = (int)v[1];
	return (offset);
}
