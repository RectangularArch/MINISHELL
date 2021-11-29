#include "minishell.h"

int	check_numeric(t_main *main, t_pcom *item)
{
	int	i;

	i = 0;
	while (item->parsed[1][i] != '\0')
	{
		if (item->parsed[1][i] != '0' && ft_isdigit(item->parsed[1][i]) == 0
		&& item->parsed[1][0] != '-' && item->parsed[1][0] != '+')
		{
			error_handler(main, item->parsed[1], 10);
			exit(main->ret_code);
		}
		i++;
	}
	return (0);
}

int	get_code(t_main *main, t_pcom *item)
{
	int	code;

	if (strncmp(item->parsed[1], "-1\0", 3) != 0)
	{
		code = ft_mini_atoi(item->parsed[1]);
		if (code == -1)
		{
			error_handler(main, item->parsed[1], 10);
			exit(main->ret_code);
		}
		if (code < 0)
			code = (code % 256) + 256;
		else
			code %= 256;
	}
	else
		code = 255;
	return (code);
}

int	run_exit(t_main *main, t_pcom *item)
{
	long long	code;
	int			i;

	i = 0;
	if (item == NULL)
		exit(main->ret_code);
	if (item->parsed[1] == NULL)
		exit(main->ret_code);
	else
		check_numeric(main, item);
	if (item->parsed[2] != NULL)
	{
		error_handler(main, NULL, 11);
		return (0);
	}
	code = get_code(main, item);
	main->ret_code = code;
	if (main->pcom_count == 1)
		ft_putstr_fd("exit\n", 1);
	exit(code);
	return (0);
}
