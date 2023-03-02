/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:30:50 by itan              #+#    #+#             */
/*   Updated: 2023/03/02 21:36:46 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_hook(int keycode, t_vars *vars)
{
	(void)vars;
	if (keycode == 1)
		ft_printf("left click\n");
	if (keycode == 2)
		ft_printf("right click\n");
	if (keycode == 3)
		ft_printf("middle click\n");
	if (keycode == 4)
		ft_printf("scroll up\n");
	if (keycode == 5)
		ft_printf("scroll down\n");
	return (0);
}
