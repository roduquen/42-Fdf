/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:11 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:25:23 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void			ft_instructions(t_fdf *params)
{
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 0, 0x00FFFFFF, "COMMANDS");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 20, 0x00FFFFFF, "UP/DOWN: ZOOM IN/OUT");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 40, 0x00FFFFFF, "LEFT/RIGHT: SWITCH DEPTH");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 60, 0x00FFFFFF, "Z-AXIS ROTATION: 7 OR 3");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 80, 0x00FFFFFF, "X-AXIS ROTATION: 8 OR 2");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 100, 0x00FFFFFF, "Y-AXIS ROTATION: 4 OR 6");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 120, 0x00FFFFFF, "CHANGE COLOR: C");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 140, 0x00FFFFFF, "RESET: R");
	mlx_string_put(params->mlx_comp.mlx_ptr, params->mlx_comp.win_command
		, 10, 160, 0x00FFFFFF, "QUIT: ESC");
}

int				closer(void *param)
{
	leave_mlx((t_fdf*)param, 0);
	exit(0);
	return (0);
}

static t_func	ft_reset(t_fdf *params)
{
	t_func	ret;

	params->rotation.z_arg = 3 * 3.14 / 2;
	params->rotation.y_arg = 3.14;
	params->move.relief = 2;
	define_matrice_x(params);
	define_matrice_y(params);
	define_matrice_z(params);
	params->move.zoom = params->mlx_comp.win_dim.length
		/ params->file.width / 1.3;
	ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH * 4);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
		, params->mlx_comp.image, 0, 0);
	translate_filepoint_to_calcpoint(params);
	if ((ret = print_point_on_renderer(params)) != SUCCESS)
		return (ret);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
		, params->mlx_comp.image, 0, 0);
	return (SUCCESS);
}

static int		key_press_next(int keycode, t_fdf *params)
{
	t_func		ret;

	if (keycode == 15)
		ft_reset(params);
	if (keycode == 8)
	{
		params->color.color += 0x234567;
		params->color.color %= 0xFF000000;
		full_list_with_color(params);
		translate_filepoint_to_calcpoint(params);
		ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH
			* 4);
		mlx_put_image_to_window(params->mlx_comp.mlx_ptr
			, params->mlx_comp.window, params->mlx_comp.image, 0, 0);
		if ((ret = print_point_on_renderer(params)) != SUCCESS)
			return (ret);
		mlx_put_image_to_window(params->mlx_comp.mlx_ptr
			, params->mlx_comp.window, params->mlx_comp.image, 0, 0);
	}
	return (0);
}

int				key_press(int keycode, void *param)
{
	if (keycode == 53)
		closer(param);
	if (keycode == 88)
		command_rotation_x((t_fdf*)param, 1);
	if (keycode == 86)
		command_rotation_x((t_fdf*)param, -1);
	if (keycode == 91)
		command_rotation_y((t_fdf*)param, -1);
	if (keycode == 84)
		command_rotation_y((t_fdf*)param, 1);
	if (keycode == 85)
		command_rotation_z((t_fdf*)param, 1);
	if (keycode == 89)
		command_rotation_z((t_fdf*)param, -1);
	if (keycode == 126)
		command_zoom((t_fdf*)param, 1);
	if (keycode == 125)
		command_zoom((t_fdf*)param, -1);
	if (keycode == 123)
		command_relief((t_fdf*)param, -1);
	if (keycode == 124)
		command_relief((t_fdf*)param, 1);
	key_press_next(keycode, (t_fdf*)param);
	return (0);
}
