/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_extra.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clovell <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:13:32 by clovell           #+#    #+#             */
/*   Updated: 2023/06/13 16:36:56 by clovell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LST_EXTRA_H
# define LST_EXTRA_H
# include "libft.h"

/*	Reads a filedes into a linked list
 *	RETURNS:
 *	A linked list where the first node is the line count,
 *	Each remaining node contains a seperate line,
 *	Last nodes content is NULL marking the end of stream.
 *	NOTE: The line count store at the first node should be: 
 *	(ft_listsize(lst) - 2)
 */
t_list	*ft_lst_readfd(int fd);
#endif
