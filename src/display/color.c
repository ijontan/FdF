/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:09:01 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 18:01:29 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	rgba_to_int(int r, int g, int b, double a)
{
	int	color;

	color = 0;
	color |= (int)(b % 256);
	color |= (int)(g % 256) << 8;
	color |= (int)(r % 256) << 16;
	color |= (int)(255 * a) % 256 << 24;
	return (color);
}

static void	hue16(int *color, int *tmp, unsigned int *hue)
{
	*tmp = (*color & 0xff000000) >> 24;
	*color = (*color & 0xff0000) >> (*hue - 5);
	*color |= *tmp;
	*color += 0x550044;
}

// my custom hue to rgb converter, but only have 24 colors
int	hue_to_int(unsigned int hue, double a)
{
	int	color;
	int	tmp;

	color = 0xff;
	hue %= 25;
	color <<= hue;
	if (hue > 16)
		hue16(&color, &tmp, &hue);
	else if (hue > 8)
	{
		tmp = (color & 0x00ff00) >> (hue - 8);
		color &= 0xff0000;
		color |= tmp;
		color += 0x554400;
	}
	else if (hue > 0)
	{
		tmp = (color & 0x0000ff) >> hue;
		color &= 0x00ff00;
		color |= tmp;
		color += 0x004444;
	}
	color |= (int)(255 * a) % 256 << 24;
	return (color);
}
