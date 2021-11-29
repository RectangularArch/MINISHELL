#include "minishell.h"

void	make_one_command(t_main *main, int temp_fd_0, int temp_fd_1)
{
	if ((main->pcomarr != NULL
			&& main->pcomarr[main->pcom_count - 1].parsed != NULL)
		|| main->input == NULL || main->is_error != 0)
	{
		if (main->is_error == 0 && main->pcomarr[0].parsed != NULL)
			handler(main);
		ft_cleaner(main);
		main->pcom_count = 1;
		dup2(temp_fd_0, 0);
		dup2(temp_fd_1, 1);
	}
}

void	make_readline(t_main *main)
{
	main->input = readline("minishell-1.0$ ");
	if (main->input == NULL)
	{
		write(1, "\e[Aminishell-1.0$ exit\n", 23);
		run_exit(main, NULL);
	}	
	if (main->input && main->input[0] != '\0')
		add_history(main->input);
}

void	minishell(t_main *main, int temp_fd_0, int temp_fd_1)
{
	while (1)
	{
		init_g_sig();
		if (!main->input && main->pcomarr == NULL)
		{
			main->pcom_count = 1;
			main->is_error = 0;
			make_readline(main);
			preparser(main->input, main);
			if (main->is_error != 0)
			{
				free (main->input);
				main->input = NULL;
				continue ;
			}	
			parser(main);
		}
		else if (main->input != NULL || main->is_semicolon != 0)
			parser(main);
		make_one_command(main, temp_fd_0, temp_fd_1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;
	int		temp_fd_0;
	int		temp_fd_1;

	(void)argv;
	(void)argc;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, sig_quit_handler);
	main = (t_main *)calloc(1, sizeof(t_main));
	main->envp_temp = envp_temp_copy(envp);
	main->ret_code = 0;
	temp_fd_0 = dup(0);
	temp_fd_1 = dup(1);
	minishell(main, temp_fd_0, temp_fd_1);
	return (0);
}
