/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_relief_and_zoom.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:13 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:03:52 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_func		command_zoom(t_fdf *params, int type)
{
	t_func		ret;

	ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH * 4);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	params->move.zoom += type;
	translate_rotatepoint_to_printpoint(params);
	if ((ret = print_point_on_renderer(params)) != SUCCESS)
		return (ret);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	return (SUCCESS);
}

t_func		command_relief(t_fdf *params, int type)
{
	t_func		ret;

	ft_memset(params->mlx_comp.renderer, 0, WINDOW_WIDTH * WINDOW_LENGTH * 4);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	params->move.relief += type / 5.0;
	translate_filepoint_to_calcpoint(params);
	if ((ret = print_point_on_renderer(params)) != SUCCESS)
		return (ret);
	mlx_put_image_to_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window
				, params->mlx_comp.image, 0, 0);
	return (SUCCESS);
}

void		full_list_with_color(t_fdf *params)
{
	t_lst_point		*begin;

	begin = params->file.point;
	while (begin)
	{
		begin->color.color = params->color.color;
		begin = begin->next;
	}
}
