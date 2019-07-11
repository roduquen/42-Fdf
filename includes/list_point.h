/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_point.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:20:34 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/09 19:42:21 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_POINT_H
# define LIST_POINT_H

/*
** Header comprenant la liste contentant les points du fichier,
**					et leur couleur,
**	les points calcule en fonction du zoom et de la rotation,
**		ainsi que les points à afficher dans la fenêtre.
*/

/*
** Includes
*/

# include "mlx_component.h"

/*
** Typedef & Structures
*/

typedef struct		s_point
{
	double		x;
	double		y;
	double		z;
}					t_point;

typedef struct		s_lst_point
{
	t_point				file;
	t_point				calcul;
	t_point				print;
	t_color				color;
	struct s_lst_point	*next;
}					t_lst_point;

#endif
