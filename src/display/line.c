/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 03:31:20 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 18:31:57 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// draws a pixel on screen of given brightness
// 0<=brightness<=1. We can use your own library
// to draw on screen

static void	change_direction(t_plotline_var *var, t_offset *offset1,
		t_offset *offset2)
{
	var->steep = absolute(offset2->y - offset1->y) > absolute(offset2->x
			- offset1->x);
	if (var->steep)
	{
		swap(&offset1->x, &offset1->y);
		swap(&offset2->x, &offset2->y);
	}
	if (offset1->x > offset2->x)
	{
		swap(&offset1->x, &offset2->x);
		swap(&offset1->y, &offset2->y);
	}
}

static void	draw_horizontal(t_vars *vars, t_plotline_var *p_var,
		t_offset *offset1, t_offset *offset2)
{
	p_var->x = offset1->x;
	while (p_var->x <= offset2->x)
	{
		p_var->offset3.x = p_var->intersect_y;
		p_var->offset3.y = p_var->x;
		p_var->offset4.x = p_var->intersect_y - 1;
		p_var->offset4.y = p_var->x;
		add_pixel(p_var->offset3, vars, hue_to_int(p_var->hue,
				rfrac_num(p_var->intersect_y)));
		add_pixel(p_var->offset4, vars, hue_to_int(p_var->hue,
				frac_num(p_var->intersect_y)));
		p_var->intersect_y += p_var->gradient;
		p_var->x++;
	}
}

static void	draw_vertical(t_vars *vars, t_plotline_var *p_var,
		t_offset *offset1, t_offset *offset2)
{
	p_var->x = offset1->x;
	while (p_var->x <= offset2->x)
	{
		p_var->offset3.y = p_var->intersect_y;
		p_var->offset3.x = p_var->x;
		p_var->offset4.y = p_var->intersect_y - 1;
		p_var->offset4.x = p_var->x;
		add_pixel(p_var->offset3, vars, hue_to_int(p_var->hue,
				rfrac_num(p_var->intersect_y)));
		add_pixel(p_var->offset4, vars, hue_to_int(p_var->hue,
				frac_num(p_var->intersect_y)));
		p_var->intersect_y += p_var->gradient;
		p_var->x++;
	}
}

void	plot_line(t_vars *vars, t_offset offset1, t_offset offset2, int hue)
{
	t_plotline_var	p_var;

	p_var.hue = hue;
	change_direction(&p_var, &offset1, &offset2);
	p_var.dx = offset2.x - offset1.x;
	p_var.dy = offset2.y - offset1.y;
	p_var.gradient = p_var.dy / p_var.dx;
	if (p_var.dx == 0.0)
		p_var.gradient = 1;
	p_var.intersect_y = offset1.y;
	if (p_var.steep)
		draw_horizontal(vars, &p_var, &offset1, &offset2);
	else
		draw_vertical(vars, &p_var, &offset1, &offset2);
}
