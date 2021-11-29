/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:38:05 by csilverb          #+#    #+#             */
/*   Updated: 2021/04/29 16:52:01 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	char			s[11];
	int				i;

	num = n;
	i = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		num = n * -1;
		write(fd, "-", 1);
	}
	while (num != 0)
	{
		s[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	while (i > 0)
		write(fd, (s + --i), 1);
}
