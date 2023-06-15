/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:49:06 by clovell           #+#    #+#             */
/*   Updated: 2023/04/25 15:49:36 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"
#include "vectormath.h"
#include <math.h>

t_vecd	vsqrmag(t_vec vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

t_vecd	vmag(t_vec vec)
{
	return (sqrt(vsqrmag(vec)));
}

t_vec	vnorm(t_vec vec)
{
	t_vecd	mag;

	mag = vmag(vec);
	if (mag == 0)
		return (vnew(0, 0));
	vec.x /= mag;
	vec.y /= mag;
	return (vec);
}
