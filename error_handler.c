#include "minishell.h"

void	error_handler4(t_main *main, char *str, int code)
{
	if (code == 13)
	{
		print_str_fd("minishell: export: `", str,
			"': not a valid identifier\n", 2);
		main->ret_code = 1;
	}
	else if (code == 14)
	{
		print_str_fd("minishell: syntax error near unexpected token\
 `", str, "'\n", 2);
		main->ret_code = 258;
	}
	else if (code == 15)
	{
		print_str_fd("minishell: ", str, ": Permission denied\n", 2);
		main->ret_code = 1;
	}
	else if (code == 16)
	{
		print_str_fd("minishell: ", str, ": No such file or directory\n", 2);
		main->ret_code = 1;
	}
}

void	error_handler3(t_main *main, char *str, int code)
{
	if (code == 9)
	{
		print_str_fd("minishell: unset: `", str,
			"': not a valid identifier\n", 2);
		main->ret_code = 1;
	}
	else if (code == 10)
	{
		print_str_fd("minishell: exit: ", str,
			": numeric argument required\n", 2);
		main->ret_code = 255;
	}
	else if (code == 11)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		main->ret_code = 1;
	}
	else if (code == 12)
	{
		print_str_fd("minishell: ", str, ": command not found\n", 2);
		main->ret_code = 127;
	}
	else
		error_handler4(main, str, code);
}

void	error_handler2(t_main *main, char *str, int code)
{
	if (code == 5)
	{
		print_str_fd("minishell: cd: ", str, ": No such file or directory\n", 2);
		main->ret_code = 1;
	}
	else if (code == 6)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		main->ret_code = 1;
	}
	else if (code == 7)
	{
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory\n", 2);
	}
	else if (code == 8)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		main->ret_code = 1;
	}
	else
		error_handler3(main, str, code);
}

void	error_handler(t_main *main, char *str, int code)
{
	if (code == 1)
	{
		print_str_fd("minishell: ", str, ": No such file or directory\n", 2);
		main->ret_code = 127;
	}
	else if (code == 2)
	{
		print_str_fd("minishell: ", str, ": is a directory\n", 2);
		main->ret_code = 126;
	}
	else if (code == 3)
	{
		print_str_fd("minishell: ", str, ": Not a directory\n", 2);
		main->ret_code = 126;
	}
	else if (code == 4)
	{
		print_str_fd("minishell: cd: ", str, ": Not a directory\n", 2);
		main->ret_code = 1;
	}
	else
		error_handler2(main, str, code);
}
