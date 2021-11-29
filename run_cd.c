#include "minishell.h"

int	cd_home(t_main *main, t_pcom *item)
{
	char	*new_path;
	int		check;
	char	*pwd;

	new_path = my_get_env(main, "HOME");
	check = chdir(new_path);
	if (check < 0 && new_path == NULL)
	{
		error_handler(main, item->parsed[1], 6);
		return (0);
	}
	else if (check < 0 && new_path[0] == '\0')
		return (0);
	else if (check < 0 && new_path != NULL)
		error_handler(main, item->parsed[1], 5);
	else
		set_old_pwd(main, my_get_env(main, "PWD"));
	pwd = getcwd(NULL, 0);
	set_pwd(main, pwd);
	free(pwd);
	return (0);
}

int	prev_cd(t_main *main, t_pcom *item)
{
	char	*pwd;
	char	*new_path;
	int		check;

	new_path = my_get_env(main, "OLDPWD");
	if (new_path == NULL)
	{
		error_handler(main, item->parsed[0], 8);
		return (0);
	}	
	check = chdir(new_path);
	if (check < 0)
	{
		error_handler(main, new_path, 5);
		return (0);
	}
	set_old_pwd(main, my_get_env(main, "PWD"));
	pwd = getcwd(NULL, 0);
	set_pwd(main, pwd);
	ft_putstr_fd(pwd, item->fd[0]);
	ft_putchar_fd('\n', item->fd[0]);
	free(pwd);
	return (0);
}

char	*null_pwd(t_main *main, t_pcom *item)
{
	char	*pwd;

	pwd = ft_strdup(my_get_env(main, "PWD"));
	if (!pwd)
		exit(errno);
	if (ft_strncmp(item->parsed[1], "..\0", 3) == 0)
	{
		error_handler(main, item->parsed[1], 7);
		free(pwd);
		pwd = ft_strjoin(my_get_env(main, "PWD"), "/..");
		if (!pwd)
			exit(errno);
	}
	else if (ft_strncmp(item->parsed[1], ".\0", 2) == 0)
	{
		error_handler(main, item->parsed[1], 7);
		free(pwd);
		pwd = ft_strjoin(my_get_env(main, "PWD"), "/.");
		if (!pwd)
			exit(errno);
	}
	return (pwd);
}

int 	run_cd(t_main *main, t_pcom *item)
{
	char	*pwd;
	int		check;

	errno = 0;
	if (item->parsed[1] == NULL || item->parsed[1][0] == '\0')
		return (cd_home(main, item));
	check = ft_strncmp(item->parsed[1], "-\0", 2);
	if (check == 0)
		return (prev_cd(main, item));
	set_old_pwd(main, my_get_env(main, "PWD"));
	check = chdir(item->parsed[1]);
	if (check != 0)
	{
		if (errno == 20)
			error_handler(main, item->parsed[1], 4);
		else if (errno == 2)
			error_handler(main, item->parsed[1], 5);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = null_pwd(main, item);
	set_pwd(main, pwd);
	free(pwd);
	return (0);
}
