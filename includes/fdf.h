/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:53:35 by itan              #+#    #+#             */
/*   Updated: 2023/03/07 17:23:31 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# ifndef QUATERNION_EPS
#  define QUATERNION_EPS (1e-4)
# endif

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	int				win_h;
	int				win_w;
}					t_vars;
typedef struct s_vertex
{
	double			v[3];
	struct s_vertex	*left;
	struct s_vertex	*right;
	struct s_vertex	*top;
	struct s_vertex	*bot;
}					t_vertex;

// credit to https://github.com/MartinWeigel/Quaternion
typedef struct s_quaternion
{
	double			w;
	double			v[3];
}					t_quaternion;

typedef struct s_offset
{
	int				x;
	int				y;
}					t_offset;

typedef struct s_fdf
{
	int				**grid;
	int				grid_width;
	int				grid_height;
	t_vertex		**v_grid;
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	char			*buffer;
}					t_fdf;

/* --------------------------------- display -------------------------------- */
void				display(t_vars *var, t_fdf *fdf);
/* ---------------------------------- parse --------------------------------- */
int					parse_map(char *file_name, t_fdf *fdf);
void				print_map(t_fdf *data);
void				create_vertices(t_fdf *fdf);

/* ---------------------------------- hooks --------------------------------- */
int					key_hook(int keycode, t_vars *vars);
int					mouse_hook(int keycode, t_vars *vars);
/* ------------------------------- projection ------------------------------- */
t_offset			isometric_projection(double v[3]);
/* ------------------------------- quaternion ------------------------------- */

void				quaternion_from_axis_angle(double axis[3], double angle,
						t_quaternion *output);
double				quaternion_to_axis_angle(t_quaternion *q, double output[3]);
void				quaternion_x_rotation(double angle, t_quaternion *output);
void				quaternion_y_rotation(double angle, t_quaternion *output);
void				quaternion_z_rotation(double angle, t_quaternion *output);
void	quaternion_from_euler3(double euler[3],
							t_quaternion *output);
void				quaternion_to_euler3(t_quaternion *q, double output[3]);
void				quaternion_conjugate(t_quaternion *q, t_quaternion *output);

t_quaternion		quaternion_create(double w, double v0, double v1,
						double v2);
t_quaternion		quaternion_create_id(void);
t_quaternion		quaternion_dup(t_quaternion *q);
bool				quaternion_equal(t_quaternion *q1, t_quaternion *q2);
double				quaternion_norm(t_quaternion *q);
void				quaternion_normalize(t_quaternion *q, t_quaternion *output);
void				quaternion_multiply(t_quaternion *q1, t_quaternion *q2,
						t_quaternion *output);
void				quaternion_rotate(t_quaternion *q, double v[3],
						double output[3]);
void				quaternion_slerp(t_quaternion *q1, t_quaternion *q2,
						double t, t_quaternion *output);
#endif