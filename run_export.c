#include "minishell.h"

void	add_to_key(t_main *main, char *arg, char *key)
{
	int		i;
	char	*temp;
	char	*value;

	i = 0;
	value = ft_strchr(arg, '=');
	value++;
	while (main->envp_temp[i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], key, ft_strlen(key)) == 0)
		{
			temp = main->envp_temp[i];
			main->envp_temp[i] = ft_strjoin(temp, value);
			if (main->envp_temp[i] == NULL)
				exit(errno);
		}
		i++;
	}
	free(temp);
}

void	change_key(t_main *main, char *arg, char *key)
{
	int		i;
	char	*temp;
	char	*old_key;

	i = 0;
	temp = NULL;
	while (main->envp_temp[i] != NULL)
	{
		old_key = get_key(main->envp_temp[i]);
		if (old_key != NULL)
		{
			if (ft_strncmp(old_key, key, ft_strlen(old_key)) == 0)
			{
				temp = main->envp_temp[i];
				main->envp_temp[i] = ft_strdup(arg);
				if (!main->envp_temp[i])
					exit(errno);
			}
			free(old_key);
		}
		i++;
	}
	free(temp);
}

int	way_to_change(t_main *main, char *arg, char *key, char *temp)
{
	if (check_env_key(main, key) != 0)
	{
		if (add_key(main, arg) < 0)
		{
			free(key);
			return (-1);
		}
	}
	else
	{
		if (temp != NULL && temp[0] == '+')
			add_to_key(main, arg, key);
		else if (temp == 0)
			return (1);
		else
			change_key(main, arg, key);
	}
	return (0);
}

static int	check_key(t_main *main, char *arg)
{
	char	*temp;
	char	*key;
	char	*plus;

	temp = ft_strchr(arg, '=');
	if (temp == arg)
		return (-1);
	plus = str_with_plus(arg);
	if (plus != NULL)
		temp = plus;
	if (temp != NULL)
		key = ft_substr(arg, 0, ft_strlen(arg) - ft_strlen(temp));
	else
		key = ft_substr(arg, 0, ft_strlen(arg));
	if (key == NULL)
		exit(errno);
	if (way_to_change(main, arg, key, temp) < 0)
		return (-1);
	free(key);
	return (0);
}

int	run_export(t_main *main, t_pcom *item)
{
	char	**new_env;
	int		i;

	main->ret_code = 0;
	i = 0;
	if (item->parsed[1] == NULL)
	{
		new_env = envp_copy(main->envp_temp);
		print_env(new_env, item->fd[1]);
		free_arr(new_env);
	}
	else
	{
		while (item->parsed[++i] != NULL)
		{
			if (check_key(main, item->parsed[i]) < 0)
				error_handler(main, item->parsed[i], 13);
		}
	}
	return (0);
}
