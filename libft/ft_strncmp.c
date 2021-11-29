/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 18:01:25 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 17:01:59 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t num)
{
	size_t	size;
	int		i;

	if (num == 0)
		return (0);
	i = 0;
	size = 0;
	while (((s1[i] == s2[i]) && (size < num - 1))
		&& ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		i++;
		size++;
	}
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
	{
		return (1);
	}
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
	{
		return (-1);
	}
	return (0);
}
