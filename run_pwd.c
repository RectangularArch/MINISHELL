#include "minishell.h"

int	run_pwd(t_main *main, t_pcom *item)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = ft_strdup(my_get_env(main, "PWD"));
		if (pwd == NULL)
			exit(errno);
	}
	ft_putstr_fd(pwd, item->fd[1]);
	ft_putstr_fd("\n", item->fd[1]);
	free(pwd);
	main->ret_code = 0;
	return (0);
}
