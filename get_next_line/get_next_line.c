/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilverb <csilverb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:49:20 by csilverb          #+#    #+#             */
/*   Updated: 2021/05/25 16:48:25 by csilverb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char		*s;
	size_t		i;
	size_t		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (s == NULL)
		return (NULL);
	while (s1[++i] != '\0')
	{
		s[i] = s1[i];
	}
	while (s2[++j] != '\0')
	{
		s[i] = s2[j];
		i++;
	}
	s[i] = '\0';
	free(s1);
	return (s);
}

int	l_count(char *result_line)
{
	int		len;
	char	is_space;

	len = 0;
	if (ft_strchr(result_line, '\n'))
		is_space = '\n';
	else
		is_space = '\0';
	while (result_line[len] != is_space)
		len++;
	return (len);
}

char	*make_read(char *result_line, int fd, int read_result)
{
	char	*buff;

	read_result = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff == NULL)
		return (NULL);
	if (result_line == NULL)
	{
		read_result = read(fd, buff, BUFFER_SIZE);
		if (read_result < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[read_result] = '\0';
		result_line = ft_strdup(buff);
	}
	while (ft_strchr(result_line, '\n') == NULL && read_result > 0)
	{
		read_result = read(fd, buff, BUFFER_SIZE);
		buff[read_result] = '\0';
		result_line = ft_strjoin_gnl(result_line, buff);
	}
	free(buff);
	return (result_line);
}

int	get_next_line(int fd, char **line)
{
	static char	*res;
	int			l;
	char		*temp;
	int			read_result;

	read_result = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	res = make_read(res, fd, read_result);
	if (res == NULL)
		return (-1);
	l = l_count(res);
	if (ft_strchr(res, '\n') != NULL)
	{
		temp = res;
		*line = ft_substr(temp, 0, l);
		res = ft_substr(temp, l + 1, ft_strlen(res) - ft_strlen(*line));
		free(temp);
		return (1);
	}
	*line = ft_substr(res, 0, l);
	free(res);
	res = NULL;
	return (0);
}
