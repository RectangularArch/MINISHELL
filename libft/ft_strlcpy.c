/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:18:20 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 17:01:37 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while ((size - 1 > 0) && (src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
