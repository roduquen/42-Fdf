/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_component.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:28:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/10 10:31:13 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_COMPONENT_H
# define MLX_COMPONENT_H

/*
** Includes
*/

# include <mlx.h>

/*
** Typedef & Structure
*/

enum				e_prog
{
	CONTINUE,
	STOP
};

typedef struct		s_size
{
	int				width;
	int				length;
}					t_size;

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	opacity;
	unsigned int	color;
}					t_color;

typedef struct		s_move
{
	double			zoom;
	double			relief;
}					t_move;

typedef struct		s_main_mlx
{
	t_size			win_dim;
	void			*mlx_ptr;
	void			*window;
	void			*image;
	void			*win_command;
	unsigned int	*renderer;
}					t_main_mlx;

#endif
