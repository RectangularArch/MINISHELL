#include "minishell.h"

static void	if_semicolon(t_main *main)
{
	if (main->is_semicolon == 0)
	{
		if (main->input != NULL)
			free (main->input);
		main->input = NULL;
	}
}

void	ft_cleaner(t_main *main)
{
	int	i;
	int	l;

	l = 0;
	while (main->pcom_count != l && main->pcomarr[l].parsed != NULL)
	{
		i = 0;
		while (ft_arr_length(main->pcomarr[l].parsed) != i)
		{
			free (main->pcomarr[l].parsed[i]);
			i++;
		}
		free (main->pcomarr[l].parsed);
		main->pcomarr[l].parsed = NULL;
		l++;
	}
	free (main->pcomarr);
	main->pcomarr = NULL;
	if_semicolon(main);
}

char	*get_lvl(char *envp)
{
	int		num;
	char	*temp;
	char	*lvl;

	temp = ft_strchr(envp, '=');
	num = ft_atoi(++temp) + 1;
	if (num < 0 || num > 998)
		num = 0;
	temp = ft_itoa(num);
	if (!temp)
		exit(errno);
	lvl = ft_strjoin("SHLVL=", temp);
	if (!lvl)
		exit(errno);
	free(temp);
	return (lvl);
}

char	*get_element(char *env_el)
{
	char	*str;

	if (ft_strncmp(env_el, "SHLVL=", 6) == 0)
		str = get_lvl(env_el);
	else
	{
		str = malloc(sizeof(char) * ft_strlen(env_el) + 1);
		if (!str)
			exit(errno);
		ft_strlcpy(str, env_el, ft_strlen(env_el) + 1);
	}
	return (str);
}

char	**envp_temp_copy(char **envp)
{
	char	**envp_temp;
	int		i;
	int		g;

	i = 0;
	g = 0;
	envp_temp = malloc(sizeof(char *) * (ft_arr_length(envp) + 2));
	if (!envp_temp)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
		{
			i++;
			continue ;
		}
		envp_temp[g] = get_element(envp[i]);
		g++;
		i++;
	}
	envp_temp[g] = ft_strdup("OLDPWD");
	if (!envp_temp[g])
		exit(errno);
	envp_temp[++g] = NULL;
	return (envp_temp);
}
