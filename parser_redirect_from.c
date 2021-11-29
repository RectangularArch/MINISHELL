#include "minishell.h"

static char	*str_edit(t_red *red, char *result_line, char *temp)
{
	if (red->string == NULL)
	{
		red->string = ft_strdup(result_line);
		find_malloc_err(red->string, errno);
	}
	else
	{
		temp = ft_strjoin(red->string, result_line);
		find_malloc_err(temp, errno);
		free (red->string);
		red->string = ft_strdup(temp);
		find_malloc_err(red->string, errno);
		free (temp);
	}
	return (temp);
}

static char	*get_from_console(t_red *red, char *line_end)
{
	char	*result_line;
	char	*temp;

	while (1)
	{
		get_next_line(0, &result_line);
		if (ft_strlen(result_line) == ft_strlen(red->arg)
			&& ft_strnstr(result_line, red->arg, 4) != NULL)
			break ;
		temp = str_edit(red, result_line, temp);
		temp = ft_strjoin(red->string, line_end);
		find_malloc_err(red->string, errno);
		free (red->string);
		red->string = ft_strdup(temp);
		find_malloc_err(red->string, errno);
		free (temp);
		free (result_line);
	}
	free (result_line);
	return (red->string);
}

static int	read_fr_args(t_red *red, t_main *main, int d, int t)
{
	while (main->input[d + 1] != '\0'
		&& ft_strchr("|;<>", main->input[d]) == NULL)
	{
		if (main->input[d] == ' ')
		{
			d++;
			red->args_len++;
			continue ;
		}
		while (main->input[d + t] != ' '
			&& ft_strchr("|;<>", main->input[d + t]) == NULL)
			t++;
		if (red->is_console != 0)
		{
			close (red->fd);
			red->fd = open(".redirection.txt", O_TRUNC | O_CREAT
					| O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
			red->is_console = 0;
		}
		ft_take_arg(t, &main->input[d], red, main);
		red->args_len += t;
		d += t;
		t = 0;
	}
	return (d);
}

static void	here_documents(t_red *red, t_main *main, int i)
{
	int		d;
	int		t;
	char	*red_arg;

	d = i;
	t = 0;
	red->args_len = -2;
	red->string = NULL;
	red_arg = NULL;
	if (red->i == 3)
	{
		red->string = get_from_console(red, "\n");
		red->fd = open(".redirection.txt", O_TRUNC | O_CREAT
				| O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
		red->is_console = 1;
		ft_putstr_fd(red->string, red->fd);
		free (red->string);
		d = read_fr_args(red, main, d, t);
		if (red->is_console == 0)
			ft_make_new_input(main, red->args_len, d);
		close (red->fd);
		red->fd = open(".redirection.txt", O_RDWR);
	}
}

void	redirect_from(t_red *red, t_main *main, t_parser *parser, int i)
{
	if (red->i == 2 || red->i == 3)
	{
		if (main->is_pipe != 0)
			red->check = 1;
		if (!main->pcomarr[main->pcom_count - 1 - red->check].parsed)
			return ;
		red->arg = main->pcomarr[main->pcom_count - 1 - red->check]
			.parsed[parser->is_space - 1];
		here_documents(red, main, i);
		if (red->i == 2)
		{
			red->fd = open(red->arg, O_RDWR);
			if (errno != 0 && parser->red_err == 0)
			{
				if (errno == 13)
					error_handler(main, red->arg, 15);
				if (errno == 2)
					error_handler(main, red->arg, 16);
				parser->red_err = 1;
			}
		}
		main->pcomarr[main->pcom_count - 1 - red->check].fd[0] = red->fd;
	}
}
