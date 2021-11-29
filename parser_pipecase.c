#include "minishell.h"

static t_pcom	*ft_realloc_pipes(t_main *main)
{
	t_pcom	*buffer;
	int		i;

	i = -1;
	buffer = ft_calloc(main->pcom_count, sizeof(t_pcom));
	find_malloc_err(buffer, errno);
	while (++i != main->pcom_count - 1)
		buffer[i] = main->pcomarr[i];
	buffer[i].fd[1] = 1;
	free(main->pcomarr);
	return (buffer);
}

static int	pipe_error(t_main *main, int i)
{
	if ((main->input[i] == '|' && main->input[i + 1] == '|')
		|| (main->input[i] == '|'
			&& main->pcomarr[main->pcom_count - 1].parsed == NULL)
		|| (main->input[i] == '|' && main->input[i + 1] == '\0'))
	{
		main->is_error = -1;
		if (main->input[i] == '|' && main->input[i + 1] == '|')
			error_handler(main, "||", 14);
		else
			error_handler(main, "|", 14);
		return (1);
	}
	return (0);
}

int	ft_pipecase(t_parser *parser, t_main *main, int i)
{
	char	*new_input;

	main->is_pipe = 0;
	if (parser->is_esc != 0)
		return (0);
	if (pipe_error(main, i) != 0)
		return (1);
	if (main->input[i] == '|' && main->input[i + 1] == '\0')
		return (1);
	if (main->input[i] == '|' && parser->o_qtes == 0
		&& parser->d_qtes == 0 && parser->is_esc == 0)
	{
		new_input = ft_strdup(&main->input[++i]);
		find_malloc_err(new_input, errno);
		free (main->input);
		main->input = new_input;
		main->pcom_count++;
		main->pcomarr = ft_realloc_pipes(main);
		main->is_pipe++;
		return (1);
	}
	return (0);
}
