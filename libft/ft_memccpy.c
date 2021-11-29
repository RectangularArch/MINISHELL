/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 15:42:44 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:51:20 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *s, int ch, size_t count)
{
	size_t	i;
	char	*src;
	char	*dest;

	i = 0;
	src = (char *)s;
	dest = (char *)dst;
	while (i != count)
	{
		dest[i] = src[i];
		if (src[i] == (char)ch)
			return (&dest[i + 1]);
		i++;
	}
	return (NULL);
}
