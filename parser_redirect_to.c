#include "minishell.h"

void	redirect_to(t_red *red, t_main *main, t_parser *parser)
{
	if (red->i == 1 || red->i == 0)
	{
		if (main->is_pipe != 0)
			red->check = 1;
		if (!main->pcomarr[main->pcom_count - 1 - red->check].parsed)
			return ;
		red->arg = main->pcomarr[main->pcom_count - 1 - red->check]
			.parsed[parser->is_space - 1];
		if (red->i == 1)
			red->fd = open(red->arg, O_WRONLY | O_APPEND
					| O_CREAT, S_IREAD | S_IWRITE);
		else
			red->fd = open(red->arg, O_TRUNC | O_CREAT
					| O_RDWR | O_APPEND, S_IREAD | S_IWRITE);
		main->pcomarr[main->pcom_count - 1 - red->check].fd[1] = red->fd;
	}
}
