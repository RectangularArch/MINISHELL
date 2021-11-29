#include "minishell.h"

static void	make_tmpath(t_main *main, t_dlc *dlc, int item)
{
	if (!main->pcomarr[0].parsed)
	{
		main->pcomarr[0].parsed = ft_calloc(2, sizeof(char *));
		find_malloc_err(main->pcomarr[0].parsed, errno);
		dlc->tmpath = ft_strdup(dlc->tmpstr);
		main->pcomarr[0].parsed[1] = NULL;
	}
	else
		dlc->tmpath = ft_strjoin(main->pcomarr[item]
				.parsed[dlc->count - 1], dlc->tmpstr);
}

static int	find_in_env(t_main *main, int i, t_dlc *dlc, int item)
{
	if (ft_strnstr(main->envp_temp[i],
			dlc->tmpath, ft_strlen(dlc->tmpath)) != NULL)
	{
		dlc->tmpstr = ft_substr(main->envp_temp[i], ft_strlen(dlc->tmpath),
				ft_strlen(main->envp_temp[i]) - ft_strlen(dlc->tmpath));
		find_malloc_err(dlc->tmpstr, errno);
		free(dlc->tmpath);
		dlc->tmpath = NULL;
		make_tmpath(main, dlc, item);
		find_malloc_err(dlc->tmpath, errno);
		if (main->pcomarr[item].parsed[dlc->count - 1])
			free(main->pcomarr[item].parsed[dlc->count - 1]);
		main->pcomarr[item].parsed[dlc->count - 1] = dlc->tmpath;
		return (-1);
	}
	if (dlc->tmpstr != NULL)
		free(dlc->tmpstr);
	return (0);
}

void	ft_replace_arg(t_main *main, int item, t_dlc *dlc, int i)
{
	dlc->count = ft_arr_length(main->pcomarr[item].parsed);
	while (main->envp_temp[++i] && dlc->tmpath != NULL)
		if (find_in_env(main, i, dlc, item) == -1)
			break ;
	if (dlc->tmpath == NULL)
	{
		if (dlc->count == 1)
		{
			main->pcomarr[0].parsed = ft_calloc(2, sizeof(char *));
			find_malloc_err(main->pcomarr[0].parsed, errno);
			dlc->tmpath = ft_strdup(dlc->tmpstr);
			find_malloc_err(dlc->tmpath, errno);
			main->pcomarr[0].parsed[1] = NULL;
		}
		else
			dlc->tmpath = ft_strjoin(main->pcomarr[item]
					.parsed[dlc->count - 1], dlc->tmpstr);
		find_malloc_err(dlc->tmpath, errno);
		if (main->pcomarr[item].parsed[dlc->count - 1])
			free(main->pcomarr[item].parsed[dlc->count - 1]);
		main->pcomarr[item].parsed[dlc->count - 1] = dlc->tmpath;
	}
}
