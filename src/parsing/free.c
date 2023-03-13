/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:49:55 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 17:54:21 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_2d(int **val, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(val[i]);
	free(val);
}

void	free_vertices(t_vertex **val, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free(val[i]);
	free(val);
}
