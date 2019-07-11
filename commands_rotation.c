/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:11:50 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/09 19:42:58 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

t_func		command_rotation_x(t_fdf *params, int type)
{
	t_func		ret;

	ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH * 4);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	params->rotation.x_arg += (type * M_PI / 90);
	if (params->rotation.x_arg >= (M_PI * 2))
		params->rotation.x_arg -= (M_PI * 2);
	define_matrice_x(params);
	translate_filepoint_to_calcpoint(params);
	if ((ret = print_point_on_renderer(params)) != SUCCESS)
		return (ret);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	return (SUCCESS);
}

t_func		command_rotation_y(t_fdf *params, int type)
{
	t_func		ret;

	ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH * 4);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	params->rotation.y_arg += (type * M_PI / 90);
	if (params->rotation.y_arg >= (M_PI * 2))
		params->rotation.y_arg -= (M_PI * 2);
	define_matrice_y(params);
	translate_filepoint_to_calcpoint(params);
	if ((ret = print_point_on_renderer(params)) != SUCCESS)
		return (ret);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	return (SUCCESS);
}

t_func		command_rotation_z(t_fdf *params, int type)
{
	t_func		ret;

	ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH * 4);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	params->rotation.z_arg += (type * M_PI / 90);
	if (params->rotation.z_arg >= (M_PI * 2))
		params->rotation.z_arg -= (M_PI * 2);
	define_matrice_z(params);
	translate_filepoint_to_calcpoint(params);
	if ((ret = print_point_on_renderer(params)) != SUCCESS)
		return (ret);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	return (SUCCESS);
}
