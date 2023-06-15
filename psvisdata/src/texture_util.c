/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:30:29 by clovell           #+#    #+#             */
/*   Updated: 2023/06/13 17:09:23 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"
#include "vectormath.h"

void	pxput(t_texture data, int x, int y, int color)
{
	char	*dst;

	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	*(unsigned int *)dst = color;
}

int	pxget(t_texture data, int x, int y)
{
	char	*dst;

	dst = data.data + (y * data.line_size + x * (data.bpp / 8));
	return (*(int *)dst);
}

t_texture	copy_tex(void *mlx, t_texture tex, const t_vec reg[2], int scale)
{
	t_texture	new;
	t_vec		size;
	t_vec		pos;
	t_vec		o;
	int			col;

	o = reg[0];
	size = vsub(reg[1], reg[0]);
	new = create_texture(mlx, size.x * scale, size.y * scale);
	pos.y = 0;
	while (pos.y < size.y * scale)
	{
		pos.x = 0;
		while (pos.x < size.x * scale)
		{
			col = pxget(tex, o.x + pos.x / scale, o.y + pos.y / scale);
			pxput(new, pos.x, pos.y, col);
			pos.x++;
		}
		pos.y++;
	}
	return (new);
}

t_texture	rotate_tex(void *mlx, t_texture t, int rot)
{
	int			y;
	int			x;
	t_texture	dst;

	dst = create_texture(mlx, t.width, t.height);
	y = 0;
	while (y < t.height)
	{
		x = 0;
		while (x < t.width)
		{
			if (rot == 1)
				pxput(dst, x, y, pxget(t, y, t.width - x - 1));
			else if (rot == 2)
				pxput(dst, x, y, pxget(t, t.width - x - 1, t.height - y - 1));
			else if (rot == 3)
				pxput(dst, x, y, pxget(t, t.height - y - 1, x));
			else
				pxput(dst, x, y, pxget(t, x, y));
			x++;
		}
		y++;
	}
	return (dst);
}
