/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:55 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:23:57 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**			Fichier C de transformation des points.
**		La première fonction sert a transformer les points
**			ayant subi une rotation en point affichable.
**		La deuxième fonction sert a transformer les points
**			ayant subi un centrage autour de l'axe principale
**				par rotation.
**		La 3ème fonction sert à centrer les points
**			récupérer depuis le fichier.
*/

void			translate_rotatepoint_to_printpoint(t_fdf *params)
{
	t_lst_point	*begin;

	begin = params->file.point;
	while (params->file.point)
	{
		params->file.point->print.x = (params->file.point->calcul.x
		* params->move.zoom)
		+ params->mlx_comp.win_dim.width / 2;
		params->file.point->print.y = (params->file.point->calcul.y
		* params->move.zoom)
		+ params->mlx_comp.win_dim.length / 2;
		params->file.point = params->file.point->next;
	}
	params->file.point = begin;
}

void			translate_calcpoint_to_rotatepoint(t_fdf *params)
{
	t_lst_point		*begin;

	begin = params->file.point;
	while (params->file.point)
	{
		calcul_x_rotation(params);
		calcul_y_rotation(params);
		calcul_z_rotation(params);
		params->file.point = params->file.point->next;
	}
	params->file.point = begin;
	translate_rotatepoint_to_printpoint(params);
}

void			translate_filepoint_to_calcpoint(t_fdf *params)
{
	t_lst_point	*begin;

	begin = params->file.point;
	while (params->file.point)
	{
		params->file.point->calcul.x = params->file.point->file.x
		- params->file.length / 2;
		params->file.point->calcul.y = params->file.point->file.y
		- params->file.width / 2;
		params->file.point->calcul.z = params->file.point->file.z
		* params->move.relief / 10;
		params->file.point = params->file.point->next;
	}
	params->file.point = begin;
	translate_calcpoint_to_rotatepoint(params);
}
