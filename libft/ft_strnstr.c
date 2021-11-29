/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 15:37:18 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 17:02:38 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hstck, const char *need, size_t l)
{
	size_t	i;
	size_t	k;
	char	*a;
	char	*b;

	i = 0;
	k = 0;
	a = (char *)hstck;
	b = (char *)need;
	if (*b == 0)
		return (a);
	while (a[i] != '\0')
	{
		k = 0;
		while (a[i + k] == b[k] && b[k] != '\0' && (i + k) < l)
		{
			if (a[i + k] == '\0')
				return (NULL);
			k++;
		}
		if (b[k] == '\0')
			return (&a[i]);
		i++;
	}
	return (NULL);
}
