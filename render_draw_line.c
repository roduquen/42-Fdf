/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_draw_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:19:44 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/09 19:16:53 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_color(t_fdf *params)
{
	params->color.color = params->color.red * 256 * 256
	+ params->color.green * 256 + params->color.blue
	+ params->color.opacity * 256 * 256 * 256;
}

void	render_draw_point(t_fdf *params, int x, int y, unsigned int color)
{
	unsigned int	i;

	i = y * WINDOW_WIDTH + x;
	params->mlx_comp.renderer[i] = color;
}
