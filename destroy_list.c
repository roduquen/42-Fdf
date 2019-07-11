/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 19:16:32 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 10:56:26 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <unistd.h>

/*
**			Fichier C de destruction de la liste.
**		La fonction commence au début de la liste et
**			en supprime les éléments un à un.
*/

t_func		destroy_list(t_fdf *params, t_func type_of_destroy)
{
	t_lst_point	*next;

	next = NULL;
	while (params->file.point)
	{
		next = params->file.point->next;
		free(params->file.point);
		params->file.point = next;
	}
	if (type_of_destroy <= -2 && type_of_destroy >= -5)
		write(2, "MLX has failed\n", 15);
	if (type_of_destroy == -11)
		write(2, "File is not formatted\n", 22);
	return (type_of_destroy);
}
