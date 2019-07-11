/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_file_to_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:27:08 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:15:08 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <unistd.h>

/*
**			Fichier C de transformation du fichier donné
**				en paramètres dans une liste.
**		La première fonction sert à vérifier que le fichier
**			est bien formaté.
**		La 2ème fonction sert à transformer les points du fichier
**			en point dans la liste.
**		La 3ème fonction sert à actualiser chaque élément.
**		La 4ème fonction sert à lire le fichier.
*/

static int			add_color_and_pos_to_point(char *buffer
	, t_lst_point *point, t_fdf *params, size_t column)
{
	char	*tmp;

	point->file.x = params->file.length;
	point->file.y = column;
	if ((point->file.z = ft_strtol(buffer, &tmp, 0)) > 1000
		|| tmp == buffer || point->file.z < -1000)
		return (-1);
	if (tmp[0] && tmp[0] == ',')
	{
		tmp++;
		point->color.color = (unsigned int)ft_strtol(tmp, &tmp, 0);
	}
	else
		point->color.color = params->color.color;
	if (tmp[0] && tmp[0] != ' ')
		return (-1);
	return (tmp - buffer);
}

static t_func		full_list_point(char *buffer, t_fdf *params)
{
	int		i;
	int		ret;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i])
	{
		while (buffer[i] && buffer[i] == ' ')
			i++;
		if (!buffer[i])
			break ;
		params->file.point->next = (t_lst_point*)malloc(sizeof(t_lst_point));
		if (!(params->file.point->next))
			return (MALLOC_ERROR);
		params->file.point = params->file.point->next;
		ft_memset(params->file.point, 0, sizeof(t_lst_point));
		if ((ret = add_color_and_pos_to_point(buffer + i, params->file.point
					, params, j)) < 0)
			return (FILE_ERROR);
		i += ret;
		j++;
	}
	return (i == 0 ? FILE_ERROR : SUCCESS);
}

static t_func		translate_line_to_list(char *buffer, t_fdf *params)
{
	t_lst_point	*begin;

	begin = params->file.point;
	while (params->file.point->next)
		params->file.point = params->file.point->next;
	if (full_list_point(buffer, params) != SUCCESS)
		return (ERROR);
	if (params->file.width < params->file.point->file.y
		&& params->file.width != 0)
		return (FILE_ERROR);
	else
		params->file.width = params->file.point->file.y;
	params->file.point = begin;
	if (begin->next->next == NULL)
		return (FILE_ERROR);
	return (SUCCESS);
}

t_func				translate_file_to_list(t_fdf *params)
{
	char		*buffer;
	int			ret;
	int			verif;

	if (!(params->file.point = (t_lst_point*)malloc(sizeof(t_lst_point))))
		return (MALLOC_ERROR);
	ft_memset(params->file.point, 0, sizeof(t_lst_point));
	buffer = NULL;
	verif = 0;
	while ((ret = get_next_line(params->fd, &buffer)) > 0)
	{
		verif++;
		if ((ret = translate_line_to_list(buffer, params)) != SUCCESS)
		{
			free(buffer);
			return (FILE_ERROR);
		}
		free(buffer);
		params->file.length++;
	}
	params->file.width++;
	if (ret == -1 || verif == 0)
		return (FILE_ERROR);
	close(params->fd);
	return (SUCCESS);
}
