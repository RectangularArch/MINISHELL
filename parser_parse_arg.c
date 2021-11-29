#include "minishell.h"

static char	**check_for_realloc(char ch, char **parsed, t_parser *parser)
{
	parsed = ft_realloc(parsed, ft_arr_length(parsed));
	find_malloc_err(parsed, errno);
	if (ch != ' ' || (ch == '$' && parser->is_esc != 0))
		parsed[ft_arr_length(parsed)] = ft_char_to_str(ch);
	else
	{
		parsed[parser->is_space - 1] = ft_strdup("\0");
		find_malloc_err(parsed, errno);
	}	
	return (parsed);
}

static char	**make_new_parsed(char ch, char **parsed, t_parser *parser, int i)
{
	parsed = ft_calloc(parser->is_space + 1, sizeof(char *));
	find_malloc_err(parsed, errno);
	if (ch == ' ' && parser->o_qtes == 0
		&& parser->d_qtes == 0 && parser->is_esc == 0)
	{
		parsed[i] = ft_strdup("\0");
		find_malloc_err(parsed, errno);
	}
	else
		parsed[i] = ft_char_to_str(ch);
	parsed[parser->is_space] = NULL;
	return (parsed);
}

char	**ft_parse_arg(char ch, char **parsed, t_parser	*parser)
{
	char	*ch_str;
	char	*tmpstr;
	int		i;

	i = 0;
	if (parsed == NULL)
	{
		parsed = make_new_parsed(ch, parsed, parser, i);
		return (parsed);
	}
	if (ft_arr_length(parsed) != parser->is_space)
		parsed = check_for_realloc(ch, parsed, parser);
	else
	{
		ch_str = ft_char_to_str(ch);
		tmpstr = ft_strjoin(parsed[parser->is_space - 1], ch_str);
		find_malloc_err(tmpstr, errno);
		if (parsed[parser->is_space - 1])
			free(parsed[parser->is_space - 1]);
		free(ch_str);
		parsed[parser->is_space - 1] = tmpstr;
	}
	return (parsed);
}
