#include "minishell.h"

static void	is_question(t_main *main, t_dlc *dlc)
{
	char	*n;

	n = ft_itoa(main->ret_code);
	dlc->tmpath = ft_strjoin(n, &dlc->tmpstr[1]);
	free (n);
}

static void	make_path(t_main *main, t_dlc *dlc)
{
	dlc->tmpath = NULL;
	if (dlc->tmpstr[0] == '?' || ft_isdigit((int)dlc->tmpstr[0]) != 0)
	{
		if (dlc->tmpstr[0] == '?')
			is_question(main, dlc);
		else
			dlc->tmpath = ft_strdup(dlc->tmpstr + 1);
		find_malloc_err(dlc->tmpath, errno);
		free (dlc->tmpstr);
		dlc->tmpstr = ft_strdup(dlc->tmpath);
		find_malloc_err(dlc->tmpstr, errno);
		free (dlc->tmpath);
		dlc->tmpath = NULL;
	}
	else
	{
		if (dlc->tmpath != NULL)
			free(dlc->tmpath);
		dlc->tmpath = ft_strjoin(dlc->tmpstr, "=");
		find_malloc_err(dlc->tmpath, errno);
		free(dlc->tmpstr);
		dlc->tmpstr = NULL;
	}
}

static char	*arg_length(char *input, t_dlc *dlc)
{
	while (ft_strchr(" \'\";\\//$=", input[0]) == NULL)
	{
		dlc->len++;
		input++;
	}
	return (input);
}

static void	free_path(t_main *main, int item, t_dlc	*dlc)
{
	if (dlc->tmpath != NULL && main->pcomarr[item].parsed == NULL)
		free (dlc->tmpath);
	else if (dlc->tmpath != NULL && main->pcomarr[item]
		.parsed[dlc->count - 1] != dlc->tmpath)
		free (dlc->tmpath);
}

int	ft_find_by_path(t_main *main, int item, char *input)
{
	t_dlc	*dlc;
	int		tot_len;

	dlc = (t_dlc *)malloc(sizeof(t_dlc));
	find_malloc_err(dlc, errno);
	tot_len = 0;
	dlc->tmpstr = NULL;
	while (input[0] == '$')
	{
		dlc->len = 0;
		input++;
		dlc->len++;
		input = arg_length(input, dlc);
		if (dlc->tmpstr != NULL)
			free(dlc->tmpstr);
		dlc->tmpstr = ft_substr(input - dlc->len, 1, dlc->len - 1);
		find_malloc_err(dlc->tmpstr, errno);
		make_path(main, dlc);
		ft_replace_arg(main, item, dlc, -1);
		tot_len += dlc->len;
		free_path(main, item, dlc);
	}
	free(dlc->tmpstr);
	free(dlc);
	return (tot_len);
}
