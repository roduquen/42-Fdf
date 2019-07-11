/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_and_leave.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 18:32:49 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:14:19 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**         Fichier C d'initialisation de la MLX.
**		La première fonction sert à quitter la MLX.
**		La 2ème fonction sert à initialiser les
**			composants de la MLX (fenêtre, rendu et
**				couleurs).
*/

t_func		leave_mlx(t_fdf *params, t_func type_of_leave)
{
	if (params->mlx_comp.image)
		mlx_destroy_image(params->mlx_comp.mlx_ptr, params->mlx_comp.image);
	if (params->mlx_comp.window)
		mlx_destroy_window(params->mlx_comp.mlx_ptr, params->mlx_comp.window);
	if (params->mlx_comp.win_command)
		mlx_destroy_window(params->mlx_comp.mlx_ptr
			, params->mlx_comp.win_command);
	return (destroy_list(params, type_of_leave));
}

t_func		init_mlx_comp(t_fdf *params)
{
	int		i;
	int		j;
	int		k;

	if (!(params->mlx_comp.mlx_ptr = mlx_init()))
		return (MLX_INIT_ERROR);
	if (!(params->mlx_comp.window = mlx_new_window(params->mlx_comp.mlx_ptr
				, WINDOW_WIDTH, WINDOW_LENGTH, "FDF")))
		return (MLX_WINDOW_ERROR);
	if (!(params->mlx_comp.win_command = mlx_new_window(params->mlx_comp.mlx_ptr
				, 400, 400, "COMMANDS")))
		return (MLX_WINDOW_ERROR);
	ft_instructions(params);
	params->move.zoom = params->mlx_comp.win_dim.length
		/ params->file.width / 1.3;
	if (!(params->mlx_comp.image = mlx_new_image(params->mlx_comp.mlx_ptr
				, WINDOW_WIDTH, WINDOW_LENGTH)))
		return (MLX_IMAGE_ERROR);
	if (!(params->mlx_comp.renderer = (unsigned int*)mlx_get_data_addr(
				params->mlx_comp.image, &i, &j, &k)))
		return (MLX_RENDERER_ERROR);
	return (SUCCESS);
}
