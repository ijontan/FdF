/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:06:41 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 17:50:12 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	**list2d_add(int **prev, int *new_item)
{
	int	**dst;
	int	len;
	int	i;

	i = -1;
	len = 0;
	if (prev == NULL)
	{
		dst = ft_calloc(2, sizeof(int *));
		dst[0] = new_item;
		dst[1] = NULL;
		return (dst);
	}
	while (prev[len])
		len++;
	dst = ft_calloc(len + 2, sizeof(int *));
	while (++i < len)
		dst[i] = prev[i];
	dst[i] = new_item;
	free(prev);
	return (dst);
}

static int	*get_line(int fd, int *width)
{
	char	*tmp;
	char	**tmp_2d;
	int		*dst;
	int		len;

	len = 0;
	tmp = get_next_line(fd);
	if (!tmp)
		return (NULL);
	tmp_2d = ft_split(tmp, ' ');
	free(tmp);
	while (tmp_2d[len] != NULL)
		len++;
	len--;
	if (*width == 0)
		*width = len;
	if (*width != len)
		exit(1);
	dst = ft_calloc(len, sizeof(int));
	while (--len >= 0)
		dst[len] = ft_atoi(tmp_2d[len]);
	while (tmp_2d[++len])
		free(tmp_2d[len]);
	free(tmp_2d);
	return (dst);
}

int	parse_map(char *file_name, t_fdf *fdf)
{
	int	fd;
	int	*tmp;
	int	**dst;

	fdf->grid_width = 0;
	fd = open(file_name, O_RDONLY);
	tmp = get_line(fd, &(fdf->grid_width));
	dst = NULL;
	while (tmp)
	{
		dst = list2d_add(dst, tmp);
		tmp = get_line(fd, &(fdf->grid_width));
	}
	fdf->grid = dst;
	fdf->grid_height = 0;
	while (dst[fdf->grid_height])
		(fdf->grid_height)++;
	ft_printf("w:%i h:%i\n", fdf->grid_width, fdf->grid_height);
	return (1);
}

void	print_map(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->grid_height)
	{
		j = 0;
		while (j < fdf->grid_width)
			ft_printf("%i ", (fdf->grid)[i][j++]);
		ft_printf("\n");
		i++;
	}
}
