/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:24:09 by clovell           #+#    #+#             */
/*   Updated: 2023/06/13 17:30:06 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mlx.h>
#include "vector.h"
#include "texture.h"
#include "program.h"

void	push_tex(t_program *pg, t_texture tex, t_vec pos)
{
	void		*mlx;
	void		*win;

	mlx = pg->mlx;
	win = pg->win;
	mlx_put_image_to_window(mlx, win, tex.img, pos.x, pos.y);
}
