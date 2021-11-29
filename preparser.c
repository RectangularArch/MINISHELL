#include "minishell.h"

typedef struct s_prep
{
	int	i;
	int	is_value;
}				t_prep;

static int	check_first_ch(char *input, t_main *main, char ch)
{
	if (input[0] == ch)
	{
		if (ch == ';')
		{
			if (input[1] == ch)
				error_handler(main, ";;", 14);
			else
				error_handler(main, ";", 14);
		}
		else if (ch == '|')
		{
			if (input[1] == ch)
				error_handler(main, "||", 14);
			else
				error_handler(main, "|", 14);
		}
		main->is_error = -1;
		return (-1);
	}
	return (0);
}

static int	check_both(char *input, t_main *main, char ch, int i)
{
	if (input[i] == ch && input[i + 1] == ch)
	{
		if (ch == ';')
			error_handler(main, ";;", 14);
		if (ch == '|')
			error_handler(main, "||", 14);
		main->is_error = -1;
		return (-1);
	}
	return (0);
}

static int	check_escape(t_main *main, char ch, t_prep *prep)
{
	if (prep->is_value != 0)
	{
		prep->is_value = 0;
		prep->i++;
		return (0);
	}
	else
	{
		if (ch == ';')
			error_handler(main, ";", 14);
		else if (ch == '|')
			error_handler(main, "|", 14);
		main->is_error = -1;
		return (-1);
	}
	return (0);
}

static void	inval_checker(char *input, t_main *main, char ch, t_prep *prep)
{
	prep->is_value = 0;
	prep->i = ft_chskip(0, " \t\n", input);
	if (check_first_ch(input, main, ch) == -1)
		return ;
	while (input[prep->i] != '\0')
	{
		while (input[prep->i] != ch && input[prep->i] != '\0')
		{
			if (ft_strchr(" \t\n", input[prep->i]) == NULL)
				prep->is_value++;
			prep->i++;
		}
		if (check_both(input, main, ch, prep->i) == -1)
			return ;
		if (input[prep->i] == ch && input[prep->i - 1] != '\\'
			&& (input[prep->i - 1] != '\'' && input[prep->i + 1] != '\'')
			&& (input[prep->i - 1] != '\"' && input[prep->i + 1] != '\"'))
		{
			if (check_escape(main, ch, prep) == -1)
				return ;
			continue ;
		}
		else
			prep->i++;
	}
}

void	preparser(char *input, t_main *main)
{
	t_prep		*prep;
	const char	arr[] = "|;";
	int			i;

	prep = (t_prep *)malloc(sizeof(t_prep));
	find_malloc_err(prep, errno);
	i = 0;
	while (arr[i] != '\0')
	{
		if (ft_strchr(input, arr[i]) != NULL)
			inval_checker(input, main, arr[i], prep);
		if (main->is_error != 0)
			break ;
		i++;
	}
	free (prep);
}
