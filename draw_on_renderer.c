/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_renderer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:41 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 12:45:57 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
**			Fichier C d'envoi des points au rendu.
**		La première fonction envoie les points du haut
**			vers le bas.
**		La deuxième fonction envoie les points de la
**			gauche vers la droite.
**		La troisième fonction appelle les 2 autres.
*/

static t_func		print_length_on_renderer(t_fdf *params)
{
	t_lst_point	*current;
	t_lst_point	*adj_point;
	t_func		ret;

	current = params->file.point->next;
	adj_point = current->next;
	while (adj_point && adj_point->file.y != current->file.y)
		adj_point = adj_point->next;
	while (adj_point)
	{
		if ((ret = draw_line(params, current, adj_point)) != SUCCESS)
			return (ret);
		adj_point = adj_point->next;
		current = current->next;
	}
	return (SUCCESS);
}

static t_func		print_width_on_renderer(t_fdf *params)
{
	t_lst_point	*current;
	t_lst_point	*adj_point;
	t_func		ret;

	current = params->file.point->next;
	adj_point = current->next;
	while (adj_point)
	{
		if ((ret = draw_line(params, current, adj_point)) != SUCCESS)
			return (ret);
		adj_point = adj_point->next;
		current = current->next;
		if (adj_point && adj_point->file.y == 0)
		{
			adj_point = adj_point->next;
			current = current->next;
		}
	}
	return (SUCCESS);
}

t_func				print_point_on_renderer(t_fdf *params)
{
	t_func		ret;

	if ((ret = print_width_on_renderer(params)) != SUCCESS)
		return (ret);
	if ((ret = print_length_on_renderer(params)) != SUCCESS)
		return (ret);
	return (SUCCESS);
}
