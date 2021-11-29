#include "minishell.h"

void	make_command(t_main *main, int i, char	*path, int exe)
{
	char	*temp;

	temp = NULL;
	if (run_build_in(main, &main->pcomarr[i], temp) == 1)
	{
		if (main->pcomarr[i].fd[0] != -1 && main->pcomarr[i].fd[1] != -1)
		{
			dup2(main->pcomarr[i].fd[0], 0);
			dup2(main->pcomarr[i].fd[1], 1);
		}
		temp = main->pcomarr[i].parsed[0];
		main->pcomarr[i].parsed[0] = path;
		exe = execve(main->pcomarr[i].parsed[0],
				main->pcomarr[i].parsed, main->envp_temp);
		main->pcomarr[i].parsed[0] = temp;
		if (exe < 0)
		{
			if (errno == 14)
			{
				error_handler(main, main->pcomarr[i].parsed[0], 12);
				exit(127);
			}
			exit(errno);
		}
	}
}

void	set_fd(t_main *main, int i, t_pipe *my_pipe)
{
	if (i > 0)
	{
		if (main->pcomarr[i].fd[0] == 0)
		{
			dup2(my_pipe[i - 1].fd[0], main->pcomarr[i].fd[0]);
			close(my_pipe[i - 1].fd[1]);
			close(my_pipe[i - 1].fd[0]);
		}
	}
	if (i != main->pcom_count - 1)
	{
		if (main->pcomarr[i].fd[1] == 1)
		{
			dup2(my_pipe[i].fd[1], main->pcomarr[i].fd[1]);
			close(my_pipe[i].fd[1]);
			close(my_pipe[i].fd[0]);
		}
	}
}

void	close_pipes(t_main *main, t_pipe *my_pipe, int i)
{
	if (i > 0)
		close(my_pipe[i - 1].fd[0]);
	if (i != main->pcom_count - 1)
		close(my_pipe[i].fd[1]);
}

void	run_all_pipes(t_main *main, t_pipe *my_pipe, int i, int pid)
{
	char	*path;

	while (i < main->pcom_count)
	{
		init_g_sig();
		path = get_path(main, main->pcomarr[i].parsed);
		pid = fork();
		if (pid == 0)
		{
			set_fd(main, i, my_pipe);
			if (main->pcomarr[i].fd[0] != -1 && main->pcomarr[i].fd[1] != -1)
			{
				make_command(main, i, path, 0);
				free (path);
			}
			else
				exit(0);
		}
		else
			g_sig[0] = 1;
		close_pipes(main, my_pipe, i);
		if (path != NULL)
			free(path);
		i++;
	}
}

int	run_pipes(t_main *main)
{
	t_pipe	*my_pipe;
	int		status;
	int		i;

	i = -1;
	my_pipe = malloc(sizeof(t_pipe) * (main->pcom_count - 1));
	if (!my_pipe)
		exit(errno);
	while (++i < main->pcom_count - 1)
		pipe(my_pipe[i].fd);
	i = 0;
	run_all_pipes(main, my_pipe, 0, 0);
	while (i < main->pcom_count)
	{
		wait(&status);
		if (status != 0)
			main->ret_code = WEXITSTATUS(status);
		i++;
	}
	if (g_sig[2] == 1)
		main->ret_code = g_sig[1];
	free(my_pipe);
	return (0);
}
