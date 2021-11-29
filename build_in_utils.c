#include "minishell.h"

static int	sign_value(char sign)
{
	if (sign == '-')
		return (-1);
	else
		return (1);
}

long long	ft_mini_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	sign = 1;
	i = 0;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = sign_value(str[i]);
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807 && sign == 1)
			return (-1);
		if (result > 9223372036854775808U && sign == -1)
			return (-1);
		i++;
	}
	return (sign * result);
}

int	check_env_key(t_main *main, char *key)
{
	int	i;
	int	cmp;

	i = 0;
	cmp = 0;
	while (main->envp_temp[i] != NULL)
	{
		if (ft_strncmp(main->envp_temp[i], key, ft_strlen(key)) == 0)
		{
			cmp = 1;
			break ;
		}
		i++;
	}
	if (cmp == 1)
		return (0);
	return (-1);
}

char	*str_with_plus(char *str)
{
	char	*plus;
	char	*ret_str;

	plus = ft_strchr(str, '+');
	if (plus != NULL)
	{
		plus++;
		if (*plus == '=')
		{
			ret_str = ft_strchr(str, '+');
			return (ret_str);
		}
	}
	return (NULL);
}

char	*get_key(char *str)
{
	char	*eq_sign;
	char	*key;

	eq_sign = ft_strchr(str, '=');
	if (eq_sign != NULL)
	{
		key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(eq_sign));
		return (key);
	}
	return (NULL);
}
