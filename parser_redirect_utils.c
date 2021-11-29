#include "minishell.h"

char	**ft_realloc_redirect(char **parsed, int count)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = ft_calloc(count + 2, sizeof(char *));
	buffer[count + 1] = NULL;
	while (i != count + 1)
	{
		buffer[i] = parsed[i];
		i++;
	}	
	free(parsed);
	return (buffer);
}

void	ft_make_new_input(t_main *main, int args_len, int d)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = ft_calloc(sizeof(char), ft_strlen(main->input) - args_len + 1);
	while (i != d - args_len)
	{
		new_str[i] = main->input[i];
		i++;
	}
	while (main->input[d] != '\0')
	{
		new_str[i] = main->input[d];
		i++;
		d++;
	}
	new_str[i] = '\0';
	free (main->input);
	main->input = new_str;
}

static char	*make_arg(int t, int i, char *str, char	*temp)
{
	temp = ft_calloc(sizeof(char), t + 1);
	find_malloc_err(temp, errno);
	temp[t] = '\0';
	while (i != t)
	{
		temp[i] = str[i];
		str[i] = ' ';
		i++;
	}
	return (temp);
}

static int	is_error(t_main *main, char	*temp)
{
	if (errno != 0)
	{
		if (errno == 13)
			error_handler(main, temp, 15);
		if (errno == 2)
			error_handler(main, temp, 16);
		free (temp);
		return (-1);
	}
	return (0);
}

void	ft_take_arg(int t, char *str, t_red *red, t_main *main)
{
	int		i;
	char	*temp;
	int		err;
	char	*result_line;

	i = 0;
	temp = NULL;
	temp = make_arg(t, i, str, temp);
	red->new_fd = open(temp, O_RDWR);
	if (is_error(main, temp) == -1)
		return ;
	err = get_next_line(red->new_fd, &result_line);
	ft_putstr_fd(result_line, red->fd);
	free (result_line);
	result_line = NULL;
	while (err != 0 && err != -1)
	{
		ft_putchar_fd('\n', red->fd);
		err = get_next_line(red->new_fd, &result_line);
		ft_putstr_fd(result_line, red->fd);
		if (result_line != NULL)
			free (result_line);
	}
	free (temp);
	close (red->new_fd);
}
