/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:11:58 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:48:12 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*s;

	s = malloc(num * size);
	if (s == NULL)
	{
		return (NULL);
	}
	ft_bzero(s, (num * size));
	return (s);
}
