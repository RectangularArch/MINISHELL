/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 19:48:45 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 17:03:07 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	g;
	int	len;

	i = 0;
	g = 0;
	if ((s1 == NULL) || (set == NULL))
		return (NULL);
	while ((s1[i] != 0) && (ft_strchr(set, s1[i])))
		i++;
	if (i == (int)(ft_strlen(s1)))
		return (ft_strdup(""));
	g = ft_strlen(s1);
	while (ft_strchr(set, s1[g - 1]))
		g--;
	len = g - i;
	return (ft_substr(s1, i, len));
}
