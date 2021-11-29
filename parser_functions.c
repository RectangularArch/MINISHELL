#include "minishell.h"

int	check_space(t_main *main, t_parser *parser, t_args *args)
{
	while (ft_strchr(" \t\n", main->input[args->i])
		&& ft_strchr(" \t\n", main->input[args->i + 1]))
		args->i++;
	if (ft_strchr("|", main->input[args->i + 1]) == NULL
		&& main->input[args->i + 1] != ';')
	{
		if (main->pcomarr[args->l].parsed != NULL
			&& ft_strchr("<>", main->input[args->i + 1]) == NULL
			&& main->pcomarr[args->l].parsed[parser->is_space - 1])
		{
			if (parser->is_redirect != 0)
			{
				make_redirect(main, args->i, parser);
				args->i++;
				return (-1);
			}
			else
				parser->is_space++;
		}
	}
	if (main->input[args->i + 1] != ';' && main->input[args->i + 1] != '|'
		&& ft_strchr("<>", main->input[args->i + 1]) == NULL)
		main->pcomarr[args->l].parsed = ft_parse_arg
			(main->input[args->i], main->pcomarr[args->l].parsed, parser);
	return (0);
}

int	quote_esc_redir(t_main *main, t_parser *parser, t_args *args)
{
	while (main->input[args->i] == '\t')
		args->i++;
	while ((main->input[args->i] == '\'' && parser->d_qtes == 0)
		|| (main->input[args->i] == '\"' && parser->o_qtes == 0))
	{
		args->i += ft_quotes(parser, main->input[args->i]);
		if (main->input[args->i] == '\0')
			return (-1);
		if (parser->is_esc != 0)
			break ;
	}
	args->i += ft_escape(parser, &main->input[args->i]);
	args->i += is_redirect(main, args->i, parser, args->l);
	return (0);
}

int	check_dollar(t_main *main, t_parser *parser, t_args *args)
{
	if (main->input[args->i] == '$' && parser->is_esc == 0
		&& parser->o_qtes == 0
		&& ft_strchr("/\\%{}[]`~", main->input[args->i + 1]) == NULL
		&& main->input[args->i + 1] != '\0')
	{
		args->i += ft_find_by_path(main, args->l, &main->input[args->i]);
		return (-1);
	}
	return (0);
}
