/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:11:47 by clovell           #+#    #+#             */
/*   Updated: 2023/05/15 14:42:38 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "texture.h"
#include "vectormath.h"
#include <mlx.h>

t_texture	create_texture(void *mlx, int width, int height)
{
	t_texture	t;

	t.width = width;
	t.height = height;
	t.img = mlx_new_image(mlx, width, height);
	t.data = mlx_get_data_addr(t.img, &t.bpp, &t.line_size, &t.endian);
	return (t);
}

t_texture	load_texture(void *mlx, char *path)
{
	t_texture	t;

	t.img = mlx_xpm_file_to_image(mlx, path, &t.width, &t.height);
	t.data = mlx_get_data_addr(t.img, &t.bpp, &t.line_size, &t.endian);
	return (t);
}
