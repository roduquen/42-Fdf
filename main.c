/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:25:53 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 13:14:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

/*
**			Fichier C de lancement du programme.
**		La première fonction écrit sur la sortie d'erreur
**			les usages de la fonction.
**		La 2ème fonction remplit les couleurs de dessin
**			avec les couleurs spécifiés par
**				l'utilisateur.
**		La 3ème fonction vérifie que l'utilisateur utilise
**			bien le programme et envoie à la deuxième
**				fonction si nécessaire.
**		Le main reprends toutes les opérations nécessaires
**			au fonctionnement du programme.
*/

static t_func	usage_fdf(t_func type_of_error)
{
	write(2, "FDF : Usage : ./fdf [PATH/FILE] -[c] [...]\n", 43);
	write(2, "Option : -c : [red] [green] [blue]\n", 35);
	write(2, "Colors red green and blue are hexadecimals from 00 to FF\n", 57);
	write(2, "By default, red green and blue are set with FF\n", 47);
	return (type_of_error);
}

static t_func	full_color_from_argv(char **argv, int i, t_fdf *params,
	char *base)
{
	unsigned char	color;
	int				j;

	color = 0;
	if (((argv[i][0] < '0' || argv[i][0] > '9')
			&& (argv[i][0] < 'A' || argv[i][0] > 'F'))
		|| ((argv[i][1] < '0' || argv[i][1] > '9')
			&& (argv[i][1] < 'A' || argv[i][1] > 'F'))
		|| (argv[i][2] != 0))
		return (USAGE_ERROR);
	j = 0;
	while (base[j] != argv[i][0])
		j++;
	color = j * 16;
	j = 0;
	while (base[j] != argv[i][0])
		j++;
	color += j;
	if (i == 3)
		params->color.red = color;
	else if (i == 4)
		params->color.green = color;
	else if (i == 5)
		params->color.blue = color;
	return (SUCCESS);
}

static t_func	check_and_full_with_argv(t_fdf *params, char **argv)
{
	int		i;

	if (open(argv[1], O_RDONLY | O_DIRECTORY) >= 0)
		return (OPEN_DIR_ERROR);
	if ((params->fd = open(argv[1], O_RDONLY)) < 0)
		return (OPEN_ERROR);
	if (argv[2])
	{
		if (argv[2][0] != '-' || argv[2][1] != 'c' || argv[2][2] != 0)
			return (USAGE_ERROR);
		i = 3;
		while (argv[i])
		{
			if (full_color_from_argv(argv, i, params, "0123456789ABCDEF")
				!= SUCCESS)
				return (USAGE_ERROR);
			i++;
		}
	}
	return (SUCCESS);
}

int				main(int argc, char **argv)
{
	t_fdf		params;
	t_func		ret;

	if (argc < 2 || argc > 6)
		return (usage_fdf(USAGE_ERROR));
	init_params(&params);
	if ((ret = check_and_full_with_argv(&params, argv)) != SUCCESS)
		return (usage_fdf(ret));
	set_color(&params);
	if ((ret = translate_file_to_list(&params)) != SUCCESS)
		return (leave_mlx(&params, ret));
	if ((ret = init_mlx_comp(&params)) != SUCCESS)
		return (leave_mlx(&params, ret));
	translate_filepoint_to_calcpoint(&params);
	if ((ret = print_point_on_renderer(&params)) != SUCCESS)
		return (leave_mlx(&params, ret));
	if (!mlx_put_image_to_window(params.mlx_comp.mlx_ptr, params.mlx_comp.window
			, params.mlx_comp.image, 0, 0))
		return (leave_mlx(&params, ERROR));
	mlx_hook(params.mlx_comp.window, 2, 0, &key_press, &params);
	mlx_hook(params.mlx_comp.window, 17, 0, &closer, &params);
	mlx_loop(params.mlx_comp.mlx_ptr);
	return (leave_mlx(&params, SUCCESS));
}
