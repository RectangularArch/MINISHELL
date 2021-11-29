#include "minishell.h"

void	set_pwd(t_main *main, char *pwd)
{
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	path = ft_strjoin("PWD=", pwd);
	if (!path)
		exit(errno);
	while (main->envp_temp[i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], "PWD=", 4) == 0)
		{
			temp = main->envp_temp[i];
			main->envp_temp[i] = path;
			free(temp);
			return ;
		}		
		i++;
	}
	add_key(main, path);
	free(path);
	free(temp);
}

char	*new_value(char *str, char *path)
{
	char	*temp;

	temp = str;
	str = path;
	free(temp);
	return (str);
}

void	set_old_pwd(t_main *main, char *pwd)
{
	char	*path;
	int		i;

	i = -1;
	if (pwd != NULL)
		pwd = ft_strdup(pwd);
	else
		pwd = ft_strdup("");
	if (!pwd)
		exit(errno);
	path = ft_strjoin("OLDPWD=", pwd);
	if (path == NULL)
		exit(errno);
	while (main->envp_temp[++i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], "OLDPWD", 6) == 0)
		{
			main->envp_temp[i] = new_value(main->envp_temp[i], path);
			free(pwd);
			return ;
		}		
	}
	add_key(main, path);
	free(path);
	free(pwd);
}
