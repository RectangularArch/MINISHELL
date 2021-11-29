#include "minishell.h"

static int	check_valid(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

static char	**rewrite_env(t_main *main, char *arg)
{
	int		i;
	int		j;
	char	**new_env;
	int		length;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (ft_arr_length(main->envp_temp)));
	while (main->envp_temp[i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], arg, ft_strlen(arg)) == 0)
		{
			i++;
			continue ;
		}
		length = ft_strlen(main->envp_temp[i]);
		new_env[j] = malloc(sizeof(char) * length + 1);
		ft_strlcpy(new_env[j], main->envp_temp[i], length + 1);
		i++;
		j++;
	}
	new_env[j] = NULL;
	free_arr(main->envp_temp);
	return (new_env);
}

static int	check_key(t_main *main, char *arg)
{
	int	i;
	int	check;

	i = 0;
	check = check_valid(arg);
	if (check < 0)
		return (-1);
	while (main->envp_temp[i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], arg, ft_strlen(arg)) == 0)
		{
			main->envp_temp = rewrite_env(main, arg);
			break ;
		}
		i++;
	}
	return (0);
}

int	run_unset(t_main *main, t_pcom *item)
{
	int		i;

	i = 1;
	main->ret_code = 0;
	if (item->parsed[1] == NULL)
		return (0);
	else
	{
		while (item->parsed[i] != NULL)
		{
			if (check_key(main, item->parsed[i]) < 0)
				error_handler(main, item->parsed[i], 9);
			i++;
		}
	}
	return (0);
}
