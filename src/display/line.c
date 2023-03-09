/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:31:20 by itan              #+#    #+#             */
/*   Updated: 2023/03/09 15:06:59 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// swaps two numbers
void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// returns absolute value of number
float	absolute(float x)
{
	if (x < 0)
		return (-x);
	else
		return (x);
}

//returns fractional part of a number
float	frac_num(float x)
{
	if (x > 0)
		return (x - (int)(x));
	else
		return (x - ((int)(x) + 1));
}

//returns 1 - fractional part of number
float	rfrac_num(float x)
{
	return (1 - frac_num(x));
}

// draws a pixel on screen of given brightness
// 0<=brightness<=1. We can use your own library
// to draw on screen

void	plot_line(t_vars *vars, t_offset offset1, t_offset offset2,int hue)
{
	int				steep;
	float			dx;
	float			dy;
	float			gradient;
	int				xpxl1;
	int				xpxl2;
	float			intersect_y;
	int				x;
	t_offset		offset3;
	t_offset		offset4;
	// unsigned int	hue;

	// hue = 5;
	steep = absolute(offset2.y - offset1.y) > absolute(offset2.x - offset1.x);
	// swap the co-ordinates if slope > 1 or we
	// draw backwards
	if (steep)
	{
		swap(&offset1.x, &offset1.y);
		swap(&offset2.x, &offset2.y);
	}
	if (offset1.x > offset2.x)
	{
		swap(&offset1.x, &offset2.x);
		swap(&offset1.y, &offset2.y);
	}
	//compute the slope
	dx = offset2.x - offset1.x;
	dy = offset2.y - offset1.y;
	gradient = dy / dx;
	if (dx == 0.0)
		gradient = 1;
	xpxl1 = offset1.x;
	xpxl2 = offset2.x;
	intersect_y = offset1.y;
	// main loop
	if (steep)
	{
		for (x = xpxl1; x <= xpxl2; x++)
		{
			offset3.x = intersect_y;
			offset3.y = x;
			offset4.x = intersect_y - 1;
			offset4.y = x;
			// add_pixel(offset3, vars, rgba_to_int(255, 255, 255,
			// 			rfrac_num(intersect_y)));
			// add_pixel(offset4, vars, rgba_to_int(255, 255, 255,
			// 			frac_num(intersect_y)));
			// add_pixel(offset3, vars, hue_to_int(hue++, rfrac_num(intersect_y)));
			// add_pixel(offset4, vars, hue_to_int(hue++, frac_num(intersect_y)));
			// (void)offset4;
			add_pixel(offset3, vars, hue_to_int(hue,rfrac_num(intersect_y)));
			add_pixel(offset4, vars, hue_to_int(hue,frac_num(intersect_y)));
			// add_pixel(offset3, vars, 0xffffffff);
			// add_pixel(offset3, vars, hue_to_int(hue++, 1));
			// add_pixel(offset3, vars,  rgba_to_int(255, 255, 255, 0.5));
			// add_pixel(offset4, vars,  rgba_to_int(255, 255, 255, 0.5));
			intersect_y += gradient;
		}
	}
	else
	{
		for (x = xpxl1; x <= xpxl2; x++)
		{
			offset3.y = intersect_y;
			offset3.x = x;
			offset4.y = intersect_y - 1;
			offset4.x = x;
			// pixel coverage is determined by fractional
			// part of y co-ordinate
			// add_pixel(offset3, vars, rgba_to_int(255, 255, 255,
			// 			rfrac_num(intersect_y)));
			// add_pixel(offset4, vars, rgba_to_int(255, 255, 255,
			// 			frac_num(intersect_y)));
			// add_pixel(offset3, vars, hue_to_int(hue++, rfrac_num(intersect_y)));
			// add_pixel(offset4, vars, hue_to_int(hue++, frac_num(intersect_y)));
			add_pixel(offset3, vars, hue_to_int(hue,rfrac_num(intersect_y)));
			add_pixel(offset4, vars, hue_to_int(hue,frac_num(intersect_y)));
			// add_pixel(offset3, vars, 0xffffffff);
			// add_pixel(offset3, vars, hue_to_int(hue++, 1));
			// add_pixel(offset3, vars,  rgba_to_int(255, 255, 255, 0.5));
			// add_pixel(offset4, vars, rgba_to_int(255, 255, 255, 0.5));
			intersect_y += gradient;
		}
	}
}
