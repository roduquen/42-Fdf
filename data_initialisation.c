/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:21 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:24:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*
** 			Fichier C d'initialisation des données.
**		Les 3 premières fonctions définissent les matrices
**			afin qu'à chaque modification de l'angle elles
**				puissent réagir directement.
**		la 4ème fonction initialise la totalité de la
**			structure qui sera dans chaque fonction.
*/

void	define_matrice_z(t_fdf *params)
{
	params->rotation.z_rot.aa = cos(params->rotation.z_arg);
	params->rotation.z_rot.ab = -sin(params->rotation.z_arg);
	params->rotation.z_rot.ac = 0;
	params->rotation.z_rot.ba = sin(params->rotation.z_arg);
	params->rotation.z_rot.bb = cos(params->rotation.z_arg);
	params->rotation.z_rot.bc = 0;
	params->rotation.z_rot.ca = 0;
	params->rotation.z_rot.cb = 0;
	params->rotation.z_rot.cc = 1;
}

void	define_matrice_y(t_fdf *params)
{
	params->rotation.y_rot.aa = cos(params->rotation.y_arg);
	params->rotation.y_rot.ab = 0;
	params->rotation.y_rot.ac = sin(params->rotation.y_arg);
	params->rotation.y_rot.ba = 0;
	params->rotation.y_rot.bb = 1;
	params->rotation.y_rot.bc = 0;
	params->rotation.y_rot.ca = -sin(params->rotation.y_arg);
	params->rotation.y_rot.cb = 0;
	params->rotation.y_rot.cc = cos(params->rotation.y_arg);
}

void	define_matrice_x(t_fdf *params)
{
	params->rotation.x_rot.aa = 1;
	params->rotation.x_rot.ab = 0;
	params->rotation.x_rot.ac = 0;
	params->rotation.x_rot.ba = 0;
	params->rotation.x_rot.bb = cos(params->rotation.x_arg);
	params->rotation.x_rot.bc = -sin(params->rotation.x_arg);
	params->rotation.x_rot.ca = 0;
	params->rotation.x_rot.cb = sin(params->rotation.x_arg);
	params->rotation.x_rot.cc = cos(params->rotation.x_arg);
}

void	init_params(t_fdf *params)
{
	ft_memset(params, 0, sizeof(t_fdf));
	params->mlx_comp.win_dim.width = WINDOW_WIDTH;
	params->mlx_comp.win_dim.length = WINDOW_LENGTH;
	params->rotation.z_arg = 3 * 3.14 / 2;
	params->rotation.y_arg = 3.14;
	params->move.relief = 2;
	params->color.red = 255;
	params->color.green = 255;
	params->color.blue = 255;
	params->color.opacity = 0;
	define_matrice_x(params);
	define_matrice_y(params);
	define_matrice_z(params);
}
