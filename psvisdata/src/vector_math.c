/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:54 by clovell           #+#    #+#             */
/*   Updated: 2023/05/15 15:19:32 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"

t_vec	vadd(t_vec f, t_vec s)
{
	t_vec	vec;

	vec.x = f.x + s.x;
	vec.y = f.y + s.y;
	return (vec);
}

t_vec	vsub(t_vec f, t_vec s)
{
	t_vec	vec;

	vec.x = f.x - s.x;
	vec.y = f.y - s.y;
	return (vec);
}

t_vec	vinv(t_vec f)
{
	t_vec	vec;

	vec.x = -f.x;
	vec.y = -f.y;
	return (vec);
}

t_vec	vmulv(t_vec f, t_vec s)
{
	t_vec	vec;

	vec.x = f.x * s.x;
	vec.y = f.y * s.y;
	return (vec);
}

t_vec	vmuls(t_vec f, float s)
{
	t_vec	vec;

	vec.x = f.x * s;
	vec.y = f.y * s;
	return (vec);
}
