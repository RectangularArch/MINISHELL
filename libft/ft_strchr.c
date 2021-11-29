/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 17:19:18 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 17:00:45 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = 0;
	if (ch == '\0')
	{
		while (str[i] != 0)
		{
			i++;
		}
		return ((char *)&str[i]);
	}
	while (str[i] != 0)
	{
		if (str[i] == ch)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
