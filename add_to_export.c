#include "minishell.h"

void	copy_with_plus(char *dest, char *src)
{
	int	i;
	int	j;
	int	plus;

	i = 0;
	j = 0;
	plus = 0;
	while (src[i] != 0)
	{
		if (src[i] == '+' && plus == 0)
		{
			plus++;
			i++;
		}
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

static int	check_valid(char *str, int plus)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break ;
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
		{
			if (str[i] == '+' && plus == 0 && str[i + 1] == '=')
			{
				plus = 1;
				i++;
				continue ;
			}
			return (-1);
		}
		i++;
	}
	if (plus == 1)
		return (1);
	return (0);
}

static char	**rewrite_env(t_main *main, char *arg, int check)
{
	int		i;
	char	**new_env;
	int		length;

	i = -1;
	new_env = malloc(sizeof(char *) * (ft_arr_length(main->envp_temp) + 2));
	if (!new_env)
		exit(errno);
	while (main->envp_temp[++i] != NULL)
	{
		length = ft_strlen(main->envp_temp[i]);
		new_env[i] = malloc(sizeof(char) * length + 1);
		if (!new_env[i])
			exit(errno);
		ft_strlcpy(new_env[i], main->envp_temp[i], length + 1);
	}
	new_env[i] = malloc(sizeof(char) * ft_strlen(arg) + 1);
	if (!new_env[i])
		exit(errno);
	if (check == 0)
		ft_strlcpy(new_env[i], arg, ft_strlen(arg) + 1);
	else
		copy_with_plus(new_env[i], arg);
	new_env[++i] = NULL;
	return (new_env);
}

int	add_key(t_main *main, char *arg)
{
	char	**new_env;
	int		check;

	check = check_valid(arg, 0);
	if (check > -1)
	{
		new_env = rewrite_env(main, arg, check);
		if (!new_env)
			return (-1);
	}	
	else
		return (-1);
	free_arr(main->envp_temp);
	main->envp_temp = new_env;
	return (0);
}
