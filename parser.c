#include "minishell.h"

static int	quote_is_printable(t_main *main, t_parser *parser, t_args *args)
{
	if (!(main->input[args->i] == '\"' && parser->is_esc != 0)
		&& !(main->input[args->i] == '\'' && parser->is_esc != 0)
		&& !(main->input[args->i] == '\"'
			&& parser->o_qtes != 0 && parser->d_qtes == 0)
		&& !(main->input[args->i] == '\''
			&& parser->o_qtes == 0 && parser->d_qtes != 0))
	{
		args->i++;
		return (-1);
	}
	parser->is_esc = 0;
	main->pcomarr[args->l].parsed = ft_parse_arg
		(main->input[args->i], main->pcomarr[args->l].parsed, parser);
	return (0);
}

static int	parse_string_cases(t_main *main, t_parser *parser, t_args *args)
{
	if (ft_strchr("\'\"", main->input[args->i])
		!= NULL && parser->is_redirect != 0)
		return (-1);
	if (ft_semicolon(parser, main, args->i))
		return (-2);
	if (ft_pipecase(parser, main, args->i))
		return (-2);
	if (check_dollar(main, parser, args) == -1)
		return (-1);
	return (0);
}

static int	parse_string(t_main *main, t_parser *parser, t_args *args)
{
	int	checker;

	if (quote_esc_redir(main, parser, args) == -1)
		return (-1);
	checker = parse_string_cases(main, parser, args);
	if (checker != 0)
		return (checker);
	if (main->input[args->i] == ' ' && parser->o_qtes == 0
		&& parser->d_qtes == 0 && parser->is_esc == 0)
	{
		if (check_space(main, parser, args) == -1)
			return (-1);
	}
	else if (ft_strchr("\'\"", main->input[args->i])
		&& main->input[args->i] != '\0')
	{
		if (quote_is_printable(main, parser, args) == -1)
			return (-1);
	}
	else
		main->pcomarr[args->l].parsed = ft_parse_arg
			(main->input[args->i], main->pcomarr[args->l].parsed, parser);
	if (main->input[args->i] != '\0')
		args->i++;
	return (0);
}

static void	make_parse(t_main *main, t_parser *parser, t_args *args)
{
	while (main->input[args->i] != '\0')
	{
		args->check = parse_string(main, parser, args);
		if (args->check == -1)
			continue ;
		else if (args->check == -2)
			break ;
	}
	if (parser->is_redirect != 0)
		make_redirect(main, args->i, parser);
	if (main->input[args->i] == '\0'
		&& main->is_semicolon == 0 && main->is_pipe == 0)
	{
		free (main->input);
		main->input = NULL;
	}
}

void	parser(t_main *main)
{
	t_args		args;
	t_parser	*parser;
	char		*temp;

	parser = (t_parser *)ft_calloc(1, sizeof(t_parser));
	find_malloc_err(parser, errno);
	parser->is_space = 1;
	parser->red_err = 0;
	args.i = 0;
	args.l = main->pcom_count - 1;
	if (!main->pcomarr)
	{
		main->pcomarr = ft_calloc(1, sizeof(t_pcom));
		main->pcomarr->fd[1] = 1;
	}
	temp = ft_strtrim(main->input, " \t\n");
	find_malloc_err(parser, errno);
	free (main->input);
	main->input = temp;
	make_parse(main, parser, &args);
	free (parser);
}
