#include "minishell.h"

int	make_fork(t_main *main, t_pcom *item)
{
	int	pid;
	int	exe;
	int	status;

	pid = fork();
	if (pid < 0)
		exit(errno);
	if (pid != 0)
	{
		g_sig[0] = 1;
		if (ft_strncmp(item->parsed[0], "minishell\0", 10) == 0)
			g_sig[0] = 2;
		wait(&status);
		if (status != 0)
			main->ret_code = WEXITSTATUS(status);
		if (main->ret_code == 2)
			error_handler(main, item->parsed[0], 12);
	}
	else
	{
		exe = execve(item->parsed[0], item->parsed, main->envp_temp);
		if (exe < 0)
			exit(errno);
	}
	return (0);
}

int	run_exe(t_main *main, t_pcom *item)
{
	char	*temp;
	char	*path;

	temp = my_get_env(main, "PATH");
	if (temp == NULL)
	{
		error_handler(main, item->parsed[0], 1);
		return (0);
	}
	path = get_path(main, item->parsed);
	if (path == NULL)
	{
		error_handler(main, item->parsed[0], 12);
		return (0);
	}
	if (path != NULL)
	{
		temp = item->parsed[0];
		item->parsed[0] = path;
		free (temp);
	}
	make_fork(main, item);
	if (g_sig[2] == 1)
		main->ret_code = g_sig[1];
	return (0);
}
