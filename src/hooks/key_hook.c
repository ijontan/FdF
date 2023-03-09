/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:16:20 by itan              #+#    #+#             */
/*   Updated: 2023/03/10 06:58:27 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 49)
	{
	}
	if (keycode == 50)
	{
	}
	if (keycode == 96)
	{
	}
	if (keycode == 65362)
	{
		vars->fdf->focal_len += 20;
		display(vars);
	}
	if (keycode == 65364)
	{
		if (vars->fdf->focal_len <= 130)
			return (1);
		vars->fdf->focal_len -= 20;
		display(vars);
	}
	(void)vars;
	ft_printf("%i\n", keycode);
	return (0);
}
