/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_rotation_point.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:06 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/09 19:44:12 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**			Fichier C de calcul de rotation.
**		La première fonction calcule les nouveaux
**			points suite à une rotation autour
**				de l'axe des x.
**		La 2ème fonction calcule les nouveaux points
**			suite à une rotation autour de l'axe des
**				y.
**		La 3ème fonction calcule les nouveaux points
**			suite à une rotation autour de l'axe des
**				z.
*/

void		calcul_x_rotation(t_fdf *params)
{
	double	y_tmp;

	y_tmp = params->file.point->calcul.y;
	params->file.point->calcul.y = params->rotation.x_rot.bb
	* params->file.point->calcul.y
	+ params->rotation.x_rot.bc * params->file.point->calcul.z;
	params->file.point->calcul.z = params->rotation.x_rot.cb * y_tmp
	+ params->rotation.x_rot.cc * params->file.point->calcul.z;
}

void		calcul_y_rotation(t_fdf *params)
{
	double	x_tmp;

	x_tmp = params->file.point->calcul.x;
	params->file.point->calcul.x = params->rotation.y_rot.aa
	* params->file.point->calcul.x
	+ params->rotation.y_rot.ac * params->file.point->calcul.z;
	params->file.point->calcul.z = params->rotation.y_rot.ca * x_tmp
	+ params->rotation.y_rot.cc * params->file.point->calcul.z;
}

void		calcul_z_rotation(t_fdf *params)
{
	double	x_tmp;

	x_tmp = params->file.point->calcul.x;
	params->file.point->calcul.x = params->rotation.z_rot.aa
	* params->file.point->calcul.x
	+ params->rotation.z_rot.ab * params->file.point->calcul.y;
	params->file.point->calcul.y = params->rotation.z_rot.ba * x_tmp
	+ params->rotation.z_rot.bb * params->file.point->calcul.y;
}
