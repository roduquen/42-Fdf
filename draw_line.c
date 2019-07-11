/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:37 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 12:52:01 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**			Fichier C d'ajout des points au rendu.
**		La première fonction dessine les lignes du
**			haut vers le bas sur le rendu.
**		La 2ème fonction dessine les lignes de la gauche
**			vers la droite si le coefficient directeur
**				n'est pas nul sur le rendu.
**		La 3ème fonction dessine les lignes de la gauche
**			vers la droite si le coefficient directeur
**				est nul sur le rendu.
**		La 4ème fonction calcule le coefficient directeur,
**			la valeur de y à l'origine et envoie aux
**				autre fonctions les données.
*/

static t_func	draw_length(t_fdf *params, t_lst_point *first
	, t_lst_point *second, t_line line)
{
	double			ret;
	double			x;

	if (line.x_equal)
		return (SUCCESS);
	x = first->print.x;
	if (x < 0)
		x = 0;
	if (x > params->mlx_comp.win_dim.width)
		x = params->mlx_comp.win_dim.width;
	while (line.xsign < 0 ? x > second->print.x : x < second->print.x)
	{
		if (x > 0 && (ret = x * line.coef + line.add) > 0
			&& x < (double)params->mlx_comp.win_dim.width
			&& ret < (double)params->mlx_comp.win_dim.length)
			render_draw_point(params, (int)x, (int)ret, first->color.color);
		x += line.xsign;
	}
	return (SUCCESS);
}

static t_func	draw_width_with_coef(t_fdf *params, t_lst_point *first,
	t_lst_point *second, t_line line)
{
	double			ret;
	double			y;

	if (line.y_equal)
		return (SUCCESS);
	y = first->print.y;
	if (y < 0)
		y = 0;
	if (y > params->mlx_comp.win_dim.length)
		y = params->mlx_comp.win_dim.length;
	while (line.ysign < 0 ? y > second->print.y : y < second->print.y)
	{
		if (y > 0 && ((ret = (y - line.add) / line.coef)) > 0
			&& ret < (double)params->mlx_comp.win_dim.width
			&& y < (double)params->mlx_comp.win_dim.length)
			render_draw_point(params, (int)ret, (int)y, first->color.color);
		y += line.ysign;
	}
	return (SUCCESS);
}

static t_func	draw_width_wout_coef(t_fdf *params, t_lst_point *first,
	t_lst_point *second, t_line line)
{
	double			y;

	if (line.y_equal)
		return (SUCCESS);
	y = first->print.y;
	if (y < 0)
		y = 0;
	if (y > params->mlx_comp.win_dim.length)
		y = params->mlx_comp.win_dim.length;
	while (line.ysign < 0 ? y > second->print.y : y < second->print.y)
	{
		if (y > 0 && first->print.x > 0
			&& first->print.x < (double)params->mlx_comp.win_dim.width
			&& y < (double)params->mlx_comp.win_dim.length)
			render_draw_point(params, (int)first->print.x, (int)y
				, first->color.color);
		y += line.ysign;
	}
	return (SUCCESS);
}

t_func			draw_line(t_fdf *params, t_lst_point *first,
	t_lst_point *second)
{
	t_line		line;
	t_func		ret;

	ft_memset(&line, 0, sizeof(t_line));
	if (first->print.x == second->print.x || first->print.y == second->print.y)
	{
		line.coef = 0;
		line.x_equal = (first->print.x == second->print.x ? 1 : 0);
		line.y_equal = (first->print.y == second->print.y ? 1 : 0);
	}
	else
		line.coef = (first->print.y - second->print.y)
		/ (first->print.x - second->print.x);
	line.add = first->print.y - line.coef * first->print.x;
	line.xsign = (first->print.x > second->print.x ? -1 : 1);
	line.ysign = (first->print.y > second->print.y ? -1 : 1);
	if ((ret = draw_length(params, first, second, line)) != SUCCESS)
		return (ret);
	if (line.coef
		&& (ret = draw_width_with_coef(params, first, second, line)) != SUCCESS)
		return (ret);
	if (!line.coef
		&& (ret = draw_width_wout_coef(params, first, second, line)) != SUCCESS)
		return (ret);
	return (SUCCESS);
}
