#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free (arr[i]);
		i++;
	}
	free (arr);
}

char	**envp_copy(char **envp)
{
	char	**envp_temp;
	int		i;

	i = 0;
	envp_temp = malloc(sizeof(char *) * (ft_arr_length(envp) + 2));
	while (envp[i] != NULL)
	{
		envp_temp[i] = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		ft_strlcpy(envp_temp[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	envp_temp[i] = NULL;
	return (envp_temp);
}

char	*my_get_env(t_main *main, char *key)
{
	int		i;
	char	*value;

	i = 0;
	while (main->envp_temp[i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], key, ft_strlen(key)) == 0)
		{
			if (main->envp_temp[i][ft_strlen(key)] == '=')
			{
				value = ft_strchr(main->envp_temp[i], '=');
				value++;
				return (value);
			}	
		}
		i++;
	}
	return (NULL);
}

void	print_str_fd(char *s1, char *s2, char *s3, int fd)
{
	char	*temp;
	char	*temp1;

	temp = ft_strjoin(s1, s2);
	temp1 = ft_strjoin(temp, s3);
	ft_putstr_fd(temp1, fd);
	free (temp);
	free (temp1);
}

char	*str_to_lower(char *arg)
{
	char	*lower;
	int		i;

	i = 0;
	lower = malloc(sizeof(char) * (ft_strlen(arg) + 1));
	if (!lower)
		exit(errno);
	while (arg[i] != '\0')
	{
		lower[i] = ft_tolower(arg[i]);
		i++;
	}
	lower[i] = '\0';
	return (lower);
}
