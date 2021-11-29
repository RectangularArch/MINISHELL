/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:03:44 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 17:00:29 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **result, int g)
{
	while (g >= 0)
	{
		free(result[g]);
		g--;
	}
	free(result);
}

static void	ft_wrtr(char **result, char const *s, char c)
{
	int		i;
	int		f;
	int		e;

	i = 0;
	f = 0;
	e = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			result[f][e] = s[i];
			e++;
		}
		if ((s[i] == c && s[i + 1] != c && e > 0) || (s[i + 1] == '\0'))
		{
			result[f][e] = '\0';
			e = 0;
			f++;
		}
		i++;
	}
}

static void	ft_memwrtr(char **result, char const *s, char c)
{
	int		i;
	int		mem;
	int		g;

	i = 0;
	mem = 0;
	g = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			mem++;
		if ((s[i] == c && s[i + 1] != c && mem > 0) || (s[i + 1] == '\0'))
		{
			result[g] = malloc((mem + 1) * sizeof(char));
			if (result[g] == NULL)
			{
				ft_free(result, g);
				break ;
			}
			mem = 0;
			g++;
		}
		i++;
	}
}

static int	ft_wrdchck(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c) && (count == 0))
		{
			count++;
		}
		else if (((s[i] == c) && (s[i + 1] != c)) && (s[i + 1] != '\0'))
		{
			count++;
		}
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		w_count;

	if (s == NULL)
		return (NULL);
	w_count = ft_wrdchck(s, c);
	result = malloc((w_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[w_count] = NULL;
	if (w_count == 0)
		return (result);
	ft_memwrtr(result, s, c);
	if (result == NULL)
		return (NULL);
	ft_wrtr(result, s, c);
	return (result);
}
