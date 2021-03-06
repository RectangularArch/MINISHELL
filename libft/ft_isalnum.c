/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:42:37 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:48:51 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int ch)
{
	if (((ch >= 48) && (ch <= 57)) || ((ch >= 65)
			&& (ch <= 90)) || ((ch >= 97) && (ch <= 122)))
	{
		return (ch);
	}
	return (0);
}
