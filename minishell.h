#ifndef MINISHELL_H
# define MINISHELL_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<dirent.h>
# include	<sys/stat.h>
# include	"./libft/libft.h"
# include	<fcntl.h>
# include	<errno.h>
# include	"./get_next_line/get_next_line.h"
# include	<readline/readline.h>
# include	<readline/history.h>
int	g_sig[3];
//[0] - pid
//[1] - error
//[2] - is_int/quit
typedef struct s_args
{
	int	i;
	int	l;
	int	check;
}				t_args;

typedef struct s_red
{
	int		i;
	char	*arg;
	int		fd;
	int		new_fd;
	int		new_len;
	int		is_console;
	char	*string;
	int		args_len;
	int		check;
}				t_red;

typedef struct s_dlc
{
	int		len;
	int		count;
	char	*tmpstr;
	char	*tmpath;
}				t_dlc;

typedef struct s_parser
{
	int	o_qtes;
	int	d_qtes;
	int	is_space;
	int	is_esc;
	int	is_redirect;
	int	redirect[4];
	int	red_err;
}				t_parser;

typedef struct s_pcom
{
	int		fd[2];
	char	**parsed;
}				t_pcom;

typedef struct s_pipe
{
	int		fd[2];
}				t_pipe;

typedef struct s_main
{
	t_pcom		*pcomarr;
	char		**envp_temp;
	char		*input;
	int			is_semicolon;
	int			is_pipe;
	int			is_error;
	int			pcom_count;
	int			ret_code;
}				t_main;

int			get_next_line(int fd, char **line);
void		preparser(char *input, t_main *main);
void		parser(t_main *main);
int			check_space(t_main *main, t_parser *parser, t_args *args);
int			quote_esc_redir(t_main *main, t_parser *parser, t_args *args);
int			check_dollar(t_main *main, t_parser *parser, t_args *args);
char		**ft_parse_arg(char ch, char **parsed, t_parser	*parser);
int			ft_quotes(t_parser *parser, char input);
int			ft_escape(t_parser *parser, char *input);
int			ft_semicolon(t_parser *parser, t_main *main, int i);
int			ft_pipecase(t_parser *parser, t_main *main, int i);
int			ft_find_by_path(t_main *main, int item, char *input);
void		ft_replace_arg(t_main *main, int item, t_dlc *dlc, int i);
int			ft_arr_length(char **arr);
char		*ft_char_to_str(char ch);
char		**ft_realloc(char **parsed, int count);
int			ft_chskip(int i, char *chars, char *input);
int			is_redirect(t_main *main, int i, t_parser *parser, int l);
void		ft_make_new_input(t_main *main, int args_len, int d);
char		**ft_realloc_redirect(char **parsed, int count);
void		make_redirect(t_main *main, int i, t_parser *parser);
void		redirect_to(t_red *red, t_main *main, t_parser *parser);
void		redirect_from(t_red *red, t_main *main, t_parser *parser, int i);
void		ft_take_arg(int t, char *str, t_red *red, t_main *main);
int			run_exe(t_main *main, t_pcom *item);
int			handler(t_main *main);
int			run_pwd(t_main *main, t_pcom *item);
int			run_unset(t_main *main, t_pcom *item);
int			run_exit(t_main *main, t_pcom *item);
int			run_env(t_main *main, t_pcom *item);
int			run_export(t_main *main, t_pcom *item);
int			run_echo(t_main *main, t_pcom *item);
int			run_cd(t_main *main, t_pcom *item);
void		print_env(char **new_env, int fd);
char		**envp_temp_copy(char **envp);
void		free_arr(char **arr);
char		**envp_copy(char **envp);
int			add_key(t_main *main, char *arg);
char		*get_path(t_main *main, char **arg);
int			run_pipes(t_main *main);
int			run_build_in(t_main *main, t_pcom *item, char *lower);
char		*my_get_env(t_main *main, char *key);
void		print_str_fd(char *s1, char *s2, char *s3, int fd);
long long	ft_mini_atoi(const char *str);
void		sig_int_handler(int sig);
void		sig_quit_handler(int sig);
void		rl_replace_line(const char *text, int clear_undo);
void		set_pwd(t_main *main, char *pwd);
void		set_old_pwd(t_main *main, char *pwd);
void		error_handler(t_main *main, char *str, int code);
char		*str_to_lower(char *arg);
int			check_env_key(t_main *main, char *key);
char		*str_with_plus(char *str);
char		*get_key(char *str);
void		init_g_sig(void);
void		find_malloc_err(void *item, errno_t error_num);
void		ft_cleaner(t_main *main);
char		**envp_temp_copy(char **envp);
int			check_pwd(t_main *main, char *str);	

#endif