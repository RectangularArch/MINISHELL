/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:27:36 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:52:36 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	size_t	len;
	char	*s;

	len = 0;
	i = 0;
	while (str[len] != 0)
	{
		len++;
	}
	s = malloc(len + 1);
	if (s == NULL)
	{
		return (NULL);
	}
	while (len > 0)
	{
		s[i] = str[i];
		len--;
		i++;
	}
	s[i] = '\0';
	return (s);
}
