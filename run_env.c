#include "minishell.h"

int	run_env(t_main *main, t_pcom *item)
{
	int		i;
	char	*equal_sign;

	i = 0;
	if (item->parsed[1] != NULL)
	{
		error_handler(main, item->parsed[0], 12);
		if (main->pcom_count > 1)
			exit(1);
		return (0);
	}
	while (main->envp_temp[i] != NULL)
	{
		equal_sign = ft_strchr(main->envp_temp[i], '=');
		if (equal_sign != NULL)
			print_str_fd(main->envp_temp[i], "\n", "\0", item->fd[1]);
		i++;
	}
	main->ret_code = 0;
	return (0);
}
