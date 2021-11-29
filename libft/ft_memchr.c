/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:38:42 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:51:24 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *memptr, int val, size_t num)
{
	size_t	i;
	char	*src;

	i = 0;
	src = (char *)memptr;
	while (i != num)
	{
		if (src[i] == val)
		{
			return (&src[i]);
		}
		i++;
	}
	return (NULL);
}
