/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:54:40 by clovell           #+#    #+#             */
/*   Updated: 2023/06/13 17:59:50 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "sort.h"

void	parse(t_sort *sort, int argc, char **argv)
{
	int	i;

	i = argc - 1;
	while (i > 0)
	{
		st_push(sort->a, ft_atoi(argv[i]));
		i--;
	}
}
