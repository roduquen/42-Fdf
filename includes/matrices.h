/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:20:37 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/09 19:20:39 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRICES_H
# define MATRICES_H

/*
**					Header des matrices de rotation.
**		La matrice x est la matrice de rotation autour de l'axe x.
**		La matrice y est la matrice de rotation autour de l'axe y.
**		La matrice z est la matrice de rotation autour de l'axe z.
**		La première lettre étant la ligne, la seconde la colonne.
*/

/*
** Typedefs & Structures
*/

/*
** 									 |   1      0      0   |
** La matrice de X est faite ainsi : |   0   cos(ß) -sin(ß)|
**			 						 |   0   sin(ß)  cos(ß)|
*/

/*
**									 | cos(ß)   0    sin(ß)|
** La matrice de Y est faite ainsi : |   0      1      0   |
**									 |-sin(ß)   0    cos(ß)|
*/

/*
**									 | cos(ß) -sin(ß)  0   |
** La matrice de Z est faite ainsi : | sin(ß)  cos(ß)  0   |
**									 |   0       0     1   |
*/

typedef struct	s_matrice
{
	double		aa;
	double		ab;
	double		ac;
	double		ba;
	double		bb;
	double		bc;
	double		ca;
	double		cb;
	double		cc;
}				t_matrice;

typedef struct	s_rotate
{
	t_matrice	x_rot;
	t_matrice	y_rot;
	t_matrice	z_rot;
	double		x_arg;
	double		y_arg;
	double		z_arg;
}				t_rotate;

#endif
