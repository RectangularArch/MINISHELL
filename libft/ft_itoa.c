/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:16:14 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:55:33 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_wrtr(char *s, unsigned int un, int n, int count)
{
	int				i;
	unsigned int	dig;
	char			*res;

	res = s;
	i = count - 1;
	dig = un;
	res[i] = '\0';
	i--;
	if (dig == 0)
	{
		res[i] = '0';
		return (res);
	}
	while (dig != 0)
	{
		res[i] = (dig % 10) + '0';
		dig /= 10;
		i--;
	}
	if (n < 0)
	{
		res[i] = '-';
	}
	return (res);
}

static int	ft_memc(int n)
{
	int		dig;
	int		mem;

	dig = n;
	if (n <= 0)
		mem = 2;
	else
		mem = 1;
	while (dig != 0)
	{
		dig /= 10;
		mem++;
	}
	return (mem);
}

char	*ft_itoa(int n)
{
	unsigned int	un;
	char			*s;

	if (n < 0)
		un = n * -1;
	else
		un = n;
	s = malloc(ft_memc(n) * sizeof(char));
	if (s == NULL)
		return (NULL);
	s = ft_wrtr(s, un, n, ft_memc(n));
	return (s);
}
