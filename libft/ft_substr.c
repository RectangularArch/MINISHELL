/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 18:48:57 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:53:26 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		s1 = malloc(1);
		s1[0] = '\0';
		return (s1);
	}
	s1 = malloc(len + 1);
	if (s1 == NULL)
		return (NULL);
	while (i != len)
	{
		s1[i] = s[i + start];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
