#include "minishell.h"

int	check_command(t_pcom *item)
{
	struct stat	*buf;
	int			check;

	buf = malloc(sizeof(struct stat));
	if (!buf)
		exit(errno);
	check = stat(item->parsed[0], buf);
	if (check == 0)
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (-1);
}

int	check_dir(t_main *main, char *str, DIR *dir, int fd)
{
	if (check_pwd(main, str) == 0 || (dir != NULL
			&& (str[ft_strlen(str) - 1] == '/'
				|| ft_strncmp(str, "./", 2) == 0
				|| ft_strncmp(str, "../", 3) == 0)))
	{
		error_handler(main, str, 2);
		closedir(dir);
		return (1);
	}
	else if (dir == NULL && (ft_strncmp(str, "./", 2) == 0
			|| ft_strncmp(str, "../", 3) == 0))
	{
		error_handler(main, str, 1);
		return (1);
	}
	else if (fd != -1 && dir == NULL && str[ft_strlen(str) - 1] == '/')
	{
		error_handler(main, str, 3);
		return (1);
	}
	if (dir != NULL)
		closedir(dir);
	return (0);
}

int	check_directory(t_main *main, t_pcom *item)
{
	DIR		*dir;
	int		fd;

	dir = opendir(item->parsed[0]);
	fd = open(item->parsed[0], O_RDONLY);
	if (dir == NULL && (ft_strncmp(item->parsed[0], "/", 1) == 0
			|| item->parsed[0][ft_strlen(item->parsed[0]) - 1] == '/'))
	{
		if (check_command(item) < 0)
			error_handler(main, item->parsed[0], 1);
		else
			return (-1);
	}
	else
	{
		if (check_dir(main, item->parsed[0], dir, fd) == 0)
			return (-1);
	}
	close (fd);
	return (0);
}

int	run_build_in(t_main *main, t_pcom *item, char *lower)
{
	lower = str_to_lower(item->parsed[0]);
	if (ft_strncmp(lower, "echo\0", 5) == 0)
		run_echo(main, item);
	else if (ft_strncmp(item->parsed[0], "cd\0", 3) == 0)
		run_cd(main, item);
	else if (ft_strncmp(lower, "pwd\0", 4) == 0)
		run_pwd(main, item);
	else if (ft_strncmp(item->parsed[0], "export\0", 7) == 0)
		run_export(main, item);
	else if (ft_strncmp(item->parsed[0], "unset\0", 6) == 0)
		run_unset(main, item);
	else if (ft_strncmp(lower, "env\0", 4) == 0)
		run_env(main, item);
	else if (ft_strncmp(item->parsed[0], "exit\0", 5) == 0)
		run_exit(main, item);
	else
	{
		free (lower);
		return (1);
	}
	if (main->pcom_count > 1)
		exit(0);
	free (lower);
	return (0);
}

int	handler(t_main *main)
{
	char	*lower;

	lower = NULL;
	if (main->pcom_count == 1)
	{
		if (main->pcomarr[0].parsed[0] == NULL)
			return (0);
		dup2(main->pcomarr[0].fd[0], 0);
		dup2(main->pcomarr[0].fd[1], 1);
		if (main->pcomarr[0].fd[0] == -1 || main->pcomarr[0].fd[1] == -1)
			return (0);
		if (main->pcomarr[0].parsed[1] == NULL)
		{
			if (check_directory(main, &main->pcomarr[0]) == 0)
				return (0);
		}
		if (run_build_in(main, &main->pcomarr[0], lower) == 1)
			run_exe(main, &main->pcomarr[0]);
		return (0);
	}
	else
		run_pipes(main);
	return (0);
}
