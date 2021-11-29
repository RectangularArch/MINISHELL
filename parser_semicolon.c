#include "minishell.h"

static int	escape_error(t_main *main, int i)
{
	if ((main->input[0] != '$' && main->input[i] == ';'
			&& main->pcomarr[main->pcom_count - 1].parsed == NULL)
		|| (main->input[i] == ';' && main->input[i + 1] == ';'))
	{
		main->is_error = -1;
		if (main->input[i] == ';' && main->input[i + 1] == ';')
			error_handler(main, ";;", 14);
		else
			error_handler(main, ";", 14);
		return (1);
	}
	return (0);
}

int	ft_semicolon(t_parser *parser, t_main *main, int i)
{
	char	*new_input;

	main->is_semicolon = 0;
	if (parser->is_esc != 0)
		return (0);
	if (escape_error(main, i) != 0)
		return (1);
	if (main->input[i] == ';' && main->input[i + 1] == '\0')
		return (1);
	if (main->input[i] == ';' && parser->o_qtes == 0
		&& parser->d_qtes == 0 && parser->is_esc == 0)
	{
		new_input = ft_strdup(&main->input[++i]);
		find_malloc_err(new_input, errno);
		free (main->input);
		main->input = new_input;
		main->is_semicolon++;
		return (1);
	}
	return (0);
}
