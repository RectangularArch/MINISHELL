/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:53:36 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:51:29 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	size_t	size;
	int		i;
	char	*s1;
	char	*s2;

	s1 = (char *)buf1;
	s2 = (char *)buf2;
	i = 0;
	size = 0;
	if (count == 0)
		return (0);
	while ((s1[i] == s2[i]) && (size < count - 1))
	{
		i++;
		size++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
