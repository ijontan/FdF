/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itan <itan@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:53:35 by itan              #+#    #+#             */
/*   Updated: 2025/06/11 22:41:28 by itan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define BUFFER_SIZE 1000
# include "libft.h"
# include <fcntl.h>
# include "mlx.h"
# include <stdbool.h>

# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include <key_linux.h>
# endif

typedef struct s_vertex
{
	double			v[3];
	struct s_vertex	*left;
	struct s_vertex	*right;
	struct s_vertex	*top;
	struct s_vertex	*bot;
}					t_vertex;

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
	int				base_hue;
	int				hue_range;
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
void				set_all_black(t_vars *var);

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

/* ---------------------------------- menu ---------------------------------- */
void				display_menu(t_vars *vars);

/* ------------------------------- projection ------------------------------- */
t_offset			orthographic_projection(double v[3]);
t_offset			perspective_projection(double v[3], double focal,
						double screen_p);

/* -------------------------------- transform ------------------------------- */
void				scale(double v[3], double scale_factor);
void				translate(double v[3], double x, double y, double z);

#endif
