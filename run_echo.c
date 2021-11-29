#include "minishell.h"

int	check_option(char *arg)
{
	int	cmp;
	int	option;

	option = 0;
	cmp = ft_strncmp(arg, "-n", 2);
	if (cmp == 0)
	{
		arg += 2;
		while (*arg == 'n')
			arg++;
		if (*arg == '\0')
			option = 1;
	}
	return (option);
}

int	print_args(t_pcom *item, int option)
{
	int	check;
	int	i;

	i = 1;
	option = 0;
	while (item->parsed[i] != NULL)
	{	
		if (option == 0)
			check = check_option(item->parsed[i]);
		while (check == 1)
		{
			option = 1;
			i++;
			if (item->parsed[i] == NULL)
				return (1);
			check = check_option(item->parsed[i]);
		}
		ft_putstr_fd(item->parsed[i], item->fd[1]);
		if (option == 0)
			option = 2;
		i++;
		if (item->parsed[i] != NULL)
			ft_putstr_fd(" ", item->fd[1]);
	}
	return (option);
}

int	run_echo(t_main *main, t_pcom *item)
{
	int	option;

	option = print_args(item, 0);
	if (option == 0 || option == 2)
		ft_putstr_fd("\n", item->fd[1]);
	main->ret_code = 0;
	return (0);
}
