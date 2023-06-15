/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectormath.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:07:05 by clovell           #+#    #+#             */
/*   Updated: 2023/04/26 18:41:02 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORMATH_H
# define VECTORMATH_H
# include "vector.h"

/* Adds a vector to another */
t_vec	vadd(t_vec f, t_vec s);

/* Subtracts a vector from another */
t_vec	vsub(t_vec f, t_vec s);

/* Inverts the components of a vector, essentially reversing the direction. */
t_vec	vinv(t_vec s);

/* Multiplies a vector by another */
t_vec	vmulv(t_vec f, t_vec s);

/* Scales the size of a vector by s */
t_vec	vmuls(t_vec f, t_vecd s);

/* Return the squared magnitude of a vector */
t_vecd	vsqrmag(t_vec vec);

/* Returns the magnitude of a vector */
t_vecd	vmag(t_vec vec);

/* Returns a normalised (length of 1) copy of a vector */
t_vec	vnorm(t_vec vec);
#endif
