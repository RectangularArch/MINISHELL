#include "minishell.h"

int	ft_chskip(int i, char *chars, char *input)
{
	while (ft_strchr(chars, input[i]))
	{
		if (input[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	ft_arr_length(char **arr)
{
	int	i;

	i = -1;
	if (!arr)
		return (1);
	while (arr[++i] != NULL)
		;
	return (i);
}

char	*ft_char_to_str(char ch)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = ch;
	str[1] = '\0';
	return (str);
}

void	find_malloc_err(void *item, errno_t error_num)
{
	if (item == NULL)
	{
		ft_putstr_fd(strerror(error_num), 1);
		exit(error_num);
	}		
}

char	**ft_realloc(char **parsed, int count)
{
	char	**buffer;
	int		i;

	i = -1;
	buffer = calloc(count + 2, sizeof(char *));
	buffer[count + 1] = NULL;
	while (++i != count + 1)
		buffer[i] = parsed[i];
	free(parsed);
	return (buffer);
}
