/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 12:57:33 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:51:43 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t count)
{
	size_t		i;
	char		*buffer;

	buffer = (char *)buf;
	i = 0;
	while (i != count)
	{
		buffer[i] = (unsigned char)ch;
		i++;
	}
	return (buffer);
}
