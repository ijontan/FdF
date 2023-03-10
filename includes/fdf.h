/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:53:35 by itan              #+#    #+#             */
/*   Updated: 2023/03/13 20:46:38 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 1000
# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# ifndef QUATERNION_EPS
#  define QUATERNION_EPS (1e-4)
# endif
# ifndef LINUX
#  define LINUX 0
# endif
# ifndef DARWIN
#  define DARWIN 0
# endif

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
typedef struct s_image
{
	int				pixel_bits;
	int				line_bytes;
	int				endian;
	char			*buffer;
}					t_image;

typedef struct s_hold
{
	double			t;
	bool			left_m;
	bool			right_m;
	bool			middle_m;
	double			prev_x;
	double			prev_y;
}					t_hold;

typedef struct s_slerp_var
{
	t_quaternion	start_o;
	t_quaternion	end_o;
	t_quaternion	out_o;
	int				sign;
	double			t;
}					t_slerp_var;

typedef struct s_fdf
{
	int				**grid;
	int				grid_width;
	int				grid_height;
	int				max_height;
	int				min_height;
	double			line_dis_2;
	double			value_weight;
	double			focal_len;
	t_vertex		**v_grid;
	t_quaternion	orientation;
	double			global_position[3];
	double			scale;
	t_slerp_var		slerp_var;
	int				cycle_per_frame;
	int				cycle_count;
	t_vertex		**v_grid_global;
	t_image			*image;
	t_hold			hold;
	int				skip;
}					t_fdf;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	int				win_h;
	int				win_w;
	t_fdf			*fdf;
}					t_vars;
/* -------------------------------- animation ------------------------------- */
void				animate_to_iso(t_vars *vars);
void				animate_to_perspec(t_vars *vars);
void				animate_to_top(t_vars *vars);

/* --------------------------------- display -------------------------------- */
void				display(t_vars *var);
int					rgba_to_int(int r, int g, int b, double a);
int					hue_to_int(unsigned int hue, double a);
void				add_pixel(t_offset offset, t_vars *var, int color);

typedef struct s_plotline_var
{
	int				steep;
	float			dx;
	float			dy;
	float			gradient;
	float			intersect_y;
	int				x;
	t_offset		offset3;
	t_offset		offset4;
	int				hue;
}					t_plotline_var;

void				plot_line(t_vars *vars, t_offset offset1, t_offset offset2,
						int hue);
void				choose_node_to_draw(t_vars *var, int i, int j, int skip);
void				swap(int *a, int *b);
float				absolute(float x);
float				frac_num(float x);
float				rfrac_num(float x);
/* ----------------------------------- err ---------------------------------- */
void				fdf_exit(t_vars *vars, int errno);

/* ---------------------------------- parse --------------------------------- */
int					parse_map(char *file_name, t_fdf *fdf);
void				print_map(t_fdf *data);
void				create_vertices(t_fdf *fdf);
void				free_2d(int **val, int len);
void				free_vertices(t_vertex **val, int len);

/* ---------------------------------- hooks --------------------------------- */
int					key_hook(int keycode, t_vars *vars);
int					mouse_hook_down(int keycode, int x, int y, t_vars *vars);
int					mouse_hook_up(int keycode, int x, int y, t_vars *vars);
int					mouse_move_hook(int x, int y, t_vars *vars);
int					loop_hook(t_vars *vars);
int					exit_hook(t_vars *vars);
/* ------------------------------- projection ------------------------------- */
t_offset			orthographic_projection(double v[3]);
t_offset			perspective_projection(double v[3], double focal,
						double screen_p);

/* ------------------------------- quaternion ------------------------------- */

void				quaternion_from_axis_angle(double axis[3], double angle,
						t_quaternion *output);
double				quaternion_to_axis_angle(t_quaternion *q, double output[3]);
void				quaternion_x_rotation(double angle, t_quaternion *output);
void				quaternion_y_rotation(double angle, t_quaternion *output);
void				quaternion_z_rotation(double angle, t_quaternion *output);

typedef struct s_e_convert_var
{
	double			cy;
	double			sy;
	double			cr;
	double			sr;
	double			cp;
	double			sp;
}					t_e_convert_var;

void				quaternion_from_euler3(double euler[3],
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

typedef struct s_q_rot_var
{
	double			ww;
	double			xx;
	double			yy;
	double			zz;
	double			wx;
	double			wy;
	double			wz;
	double			xy;
	double			xz;
	double			yz;
}					t_q_rot_var;

void				quaternion_rotate(t_quaternion *q, double v[3],
						double output[3]);

typedef struct s_q_slerp_var
{
	double			cos_half_theta;
	double			half_theta;
	double			sin_half_theta;
	double			ratio_a;
	double			ratio_b;
	t_quaternion	*q1;
	t_quaternion	*q2;
}					t_q_slerp_var;

void				quaternion_slerp(t_quaternion *q1, t_quaternion *q2,
						double t, t_quaternion *output);
/* -------------------------------- transform ------------------------------- */
void				scale(double v[3], double scale_factor);
void				translate(double v[3], double x, double y, double z);

#endif