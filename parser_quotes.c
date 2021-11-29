#include "minishell.h"

int	ft_quotes(t_parser *parser, char input)
{
	if (input == '\"')
	{
		if (parser->is_esc != 0)
			return (0);
		if (parser->d_qtes == 0 && parser->o_qtes == 0 && parser->is_esc == 0)
			parser->d_qtes++;
		else if (parser->d_qtes != 0)
			parser->d_qtes--;
		if (input == '\"' && parser->d_qtes == 0 && parser->o_qtes != 0)
			return (0);
		return (1);
	}
	else if (input == '\'')
	{	
		if (parser->is_esc != 0)
			return (0);
		if (parser->o_qtes == 0 && parser->d_qtes == 0 && parser->is_esc == 0)
			parser->o_qtes++;
		else if (parser->o_qtes != 0)
			parser->o_qtes--;
		if (input == '\'' && parser->o_qtes == 0 && parser->d_qtes != 0)
			return (0);
		return (1);
	}
	return (0);
}
