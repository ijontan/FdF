/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:16:44 by itan              #+#    #+#             */
/*   Updated: 2023/03/14 00:20:10 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_hook(t_vars *vars)
{
	ft_printf("%sexiting the program%s\n", "\033[1;33m", "\033[0m");
	fdf_exit(vars, 0);
	return (1);
}