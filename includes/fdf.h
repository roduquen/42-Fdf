/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:20:28 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:04:22 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** Include
*/

# include "libft.h"
# include "list_point.h"
# include "matrices.h"
# include "mlx_component.h"

/*
** Macro
*/

# define WINDOW_WIDTH 1440
# define WINDOW_LENGTH 810

/*
** Typedef & Structure
*/

typedef enum		e_func
{
	SUCCESS = 0,
	ERROR = -1,
	MLX_INIT_ERROR = -2,
	MLX_WINDOW_ERROR = -3,
	MLX_IMAGE_ERROR = -4,
	MLX_RENDERER_ERROR = -4,
	MLX_COLOR_ERROR = -5,
	OPEN_DIR_ERROR = -6,
	USAGE_ERROR = -7,
	OPEN_ERROR = -8,
	MALLOC_ERROR = -9,
	READ_ERROR = -10,
	FILE_ERROR = -11,
	DRAW_ERROR = -12,
	CLEAR_ERROR = -13
}					t_func;

typedef struct		s_line
{
	double	coef;
	char	x_equal;
	char	y_equal;
	double	add;
	double	xsign;
	double	ysign;
}					t_line;

typedef struct s_lst_point	t_lst_point;

typedef struct		s_file
{
	size_t		length;
	size_t		width;
	int			max_height;
	int			min_height;
	t_lst_point	*point;
}					t_file;

typedef struct		s_fdf
{
	int				fd;
	t_color			color;
	t_move			move;
	t_rotate		rotation;
	t_main_mlx		mlx_comp;
	t_file			file;
}					t_fdf;

/*
** Initialisation & Leave
*/

void				init_params(t_fdf *params);
void				set_color(t_fdf *params);
t_func				init_mlx_comp(t_fdf *params);
t_func				leave_mlx(t_fdf *params, t_func type_of_leave);
t_func				destroy_list(t_fdf *params, t_func type_of_destroy);

/*
** Translation
*/

t_func				translate_file_to_list(t_fdf *params);
void				translate_filepoint_to_calcpoint(t_fdf *params);
void				translate_calcpoint_to_rotatepoint(t_fdf *params);
void				translate_rotatepoint_to_printpoint(t_fdf *params);

/*
** Calcul
*/

void				full_list_with_color(t_fdf *params);
void				define_matrice_x(t_fdf *params);
void				calcul_x_rotation(t_fdf *params);
void				define_matrice_y(t_fdf *params);
void				calcul_y_rotation(t_fdf *params);
void				define_matrice_z(t_fdf *params);
void				calcul_z_rotation(t_fdf *params);

/*
** Draw_utility
*/

void				ft_instructions(t_fdf *params);
void				render_draw_point(t_fdf *params, int x, int y
	, unsigned int color);
t_func				draw_line(t_fdf *params, t_lst_point *first,
	t_lst_point *second);
t_func				print_point_on_renderer(t_fdf *params);

/*
** Command
*/

int					key_press(int keycode, void *param);
int					closer(void *param);
int					command_rotation_x(t_fdf *params, int type);
t_func				command_rotation_y(t_fdf *params, int type);
t_func				command_rotation_z(t_fdf *params, int type);
t_func				command_zoom(t_fdf *params, int type);
t_func				command_relief(t_fdf *params, int type);

#endif
