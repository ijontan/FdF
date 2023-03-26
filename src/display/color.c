/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 02:09:01 by itan              #+#    #+#             */
/*   Updated: 2023/03/27 03:16:58 by itan             ###   ########.fr       */
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

// my custom hue to rgb converter, but only have 24 colors
int	hue_to_int(unsigned int hue, double a)
{
	int	color;

	color = 0;
	hue %= 766;
	if (hue < 256)
	{
		color |= (int)(255 - hue % 256);
		color |= (int)(hue % 256) << 8;
	}
	else if (hue < 511)
	{
		color |= (int)(255 - (hue - 255) % 256) << 8;
		color |= (int)((hue - 255) % 256) << 16;
	}
	else if (hue < 766)
	{
		color |= (int)(255 - (hue - 510) % 256) << 16;
		color |= (int)((hue - 510) % 256);
	}
	color |= (int)(255 * a) % 256 << 24;
	return (color);
}
