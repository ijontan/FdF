/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:53:35 by itan              #+#    #+#             */
/*   Updated: 2023/03/02 13:10:39 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_matrix
{
	double	r1c1;
	double	r2c1;
	double	r3c1;
	double	r1c2;
	double	r2c2;
	double	r3c2;
	double	r1c3;
	double	r2c3;
	double	r3c3;
}			t_matrix;

typedef struct fdf
{
	/* data */
}			t_fdf;

#endif