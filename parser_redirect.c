#include "minishell.h"

static int	redirect_to_case(t_parser *parser, t_main *main, int i, int result)
{
	if (main->input[i] == '>')
	{
		if (parser->is_redirect != 0)
			make_redirect(main, i, parser);
		if (main->input[i + 1] == '>')
		{
			parser->redirect[1] = 1;
			result += 2;
		}
		else
		{
			parser->redirect[0] = 1;
			result++;
		}
		parser->is_redirect++;
	}
	return (result);
}

static int	redirect_fr_case(t_parser *parser, t_main *main, int i, int result)
{
	if (main->input[i] == '<')
	{
		if (parser->is_redirect != 0)
			make_redirect(main, i, parser);
		if (main->input[i + 1] == '<')
		{
			parser->redirect[3] = 1;
			result += 2;
		}
		else
		{
			parser->redirect[2] = 1;
			result++;
		}
		parser->is_redirect++;
	}
	return (result);
}

int	is_redirect(t_main *main, int i, t_parser *parser, int l)
{
	int	result;

	result = 0;
	if (parser->o_qtes != 0 || parser->d_qtes != 0 || parser->is_esc != 0)
		return (result);
	result = redirect_to_case(parser, main, i, result);
	result = redirect_fr_case(parser, main, i, result);
	if (!main->pcomarr[l].parsed)
		return (result);
	if (result != 0 && main->input[i] + result != ' '
		&& main->pcomarr[l].parsed[parser->is_space - 1])
		parser->is_space++;
	return (result);
}

void	make_redirect(t_main *main, int i, t_parser *parser)
{
	t_red	*red;

	red = (t_red *)malloc(sizeof(t_red));
	find_malloc_err(red, errno);
	red->i = 0;
	red->check = 0;
	while (red->i != 4)
	{
		if (parser->redirect[red->i] != 0)
			break ;
		red->i++;
	}
	redirect_to(red, main, parser);
	redirect_from(red, main, parser, i);
	red->new_len = ft_arr_length
		(main->pcomarr[main->pcom_count - 1 - red->check].parsed) - 2;
	main->pcomarr[main->pcom_count - 1 - red->check]
		.parsed = ft_realloc_redirect
		(main->pcomarr[main->pcom_count - 1 - red->check].parsed, red->new_len);
	parser->redirect[red->i] = 0;
	parser->is_redirect = 0;
	free (red->arg);
	free (red);
}
