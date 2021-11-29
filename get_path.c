#include "minishell.h"

int	check_pwd(t_main *main, char *str)
{
	char	*temp;

	temp = my_get_env(main, "OLDPWD");
	if (temp != NULL)
	{
		if (ft_strncmp(str, temp, ft_strlen(str)) == 0)
			return (0);
	}
	temp = my_get_env(main, "PWD");
	if (temp != NULL)
	{
		if (ft_strncmp(str, temp, ft_strlen(str)) == 0)
			return (0);
	}
	return (1);
}

int	check_path(char *path)
{
	struct stat	*buf;
	int			check;
	DIR			*dir;

	buf = malloc(sizeof(struct stat));
	dir = opendir(path);
	if (buf == NULL)
		return (-1);
	check = stat(path, buf);
	if (check == 0 && dir == NULL)
	{
		free(buf);
		return (0);
	}
	if (dir != NULL)
		closedir(dir);
	free(buf);
	return (-1);
}

char	*check_all_path(char **paths, char *arg)
{
	char	*temp;
	char	*result;
	int		i;
	int		check;

	i = 0;
	check = -1;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			exit(errno);
		result = ft_strjoin(temp, arg);
		if (result == NULL)
			exit(errno);
		free(temp);
		check = check_path(result);
		if (check == 0)
			return (result);
		free(result);
		i++;
	}
	if (check < 0)
		return (NULL);
	return (result);
}

char	*get_path(t_main *main, char **arg)
{
	char	*for_parse;
	char	**paths;
	char	*temp;

	if (!arg[0] || !arg[0][0])
		return (NULL);
	if (check_path(arg[0]) == 0)
		return (ft_strdup(arg[0]));
	for_parse = my_get_env(main, "PATH");
	paths = ft_split(for_parse, ':');
	if (paths == NULL)
		exit(errno);
	temp = check_all_path(paths, arg[0]);
	if (temp == NULL)
	{
		free_arr(paths);
		return (NULL);
	}
	free_arr(paths);
	return (temp);
}
