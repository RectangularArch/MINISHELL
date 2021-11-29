#include "minishell.h"

int	ft_escape(t_parser *parser, char *input)
{
	char	*pntr;
	char	pos;

	pos = input[1];
	parser->is_esc = 0;
	if (*input == '\\' && parser->o_qtes == 0)
	{
		if (parser->d_qtes != 0 && pos != '$' && pos != '\"' && pos != '\\')
			return (0);
		pntr = ft_strchr("\\$\"", pos);
		if (parser->d_qtes == 0)
			parser->is_esc++;
		else if (parser->d_qtes != 0)
			parser->is_esc++;
		else if (pntr != NULL && *pntr != '\0')
			parser->is_esc++;
		return (1);
	}
	return (0);
}
