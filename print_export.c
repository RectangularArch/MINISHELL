#include "minishell.h"

void	sort_env(char **new_env)
{
	char	*temp;
	int		i;
	int		j;
	int		count;
	int		cmp;

	i = 0;
	j = 0;
	count = ft_arr_length(new_env);
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1)
		{
			cmp = ft_strncmp(new_env[j], new_env[j + 1], ft_strlen(new_env[j]));
			if (cmp > 0)
			{
				temp = new_env[j];
				new_env[j] = new_env[j + 1];
				new_env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	*env_transform(char *str)
{
	char	*trans_str;
	int		i;
	int		j;
	int		is_sign;

	i = 0;
	j = 0;
	is_sign = 0;
	trans_str = malloc(sizeof(char) * (ft_strlen(str) + 3));
	while (str[i] != 0)
	{
		trans_str[j] = str[i];
		if (str[i] == '=' && is_sign == 0)
		{
			is_sign = 1;
			j++;
			trans_str[j] = '"';
		}
		i++;
		j++;
	}
	if (ft_strchr(str, '=') != NULL)
		trans_str[j] = '"';
	trans_str[++j] = '\0';
	return (trans_str);
}

void	print_env(char **new_env, int fd)
{
	int		i;
	char	*temp;

	i = 0;
	sort_env(new_env);
	while (new_env[i] != NULL)
	{
		temp = env_transform(new_env[i]);
		print_str_fd("declare -x ", temp, "\n", fd);
		free(temp);
		i++;
	}
}
