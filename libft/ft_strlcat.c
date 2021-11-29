/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 16:37:23 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:52:46 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	dst_l;

	dst_l = ft_strlen(dst);
	i = 0;
	if (dst_l >= size)
		return (ft_strlen(src) + size);
	if (size == 0)
		return (ft_strlen(src) + dst_l);
	while ((size - dst_l - 1 > 0) && (src[i] != '\0'))
	{
		dst[dst_l + i] = src[i];
		i++;
		size--;
	}
	dst[dst_l + i] = '\0';
	return (ft_strlen(src) + dst_l);
}
