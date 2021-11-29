/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:17:52 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:52:41 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	while (i != ft_strlen(s1))
	{
		s[i] = s1[i];
		i++;
	}
	while (j != ft_strlen(s2))
	{
		s[i] = s2[j];
		j++;
		i++;
	}
	s[i] = '\0';
	return (s);
}
