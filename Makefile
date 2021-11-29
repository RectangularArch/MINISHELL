NAME = minishell

LIBFT = ./libft/libft.a

READLINE_LIB = -lreadline -L/Users/$(USER)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(USER)/.brew/Cellar/readline/8.1/include 

SRCS =  main.c \
		run_exe.c \
		handler.c \
		run_cd.c \
		run_pwd.c \
		run_env.c \
		run_echo.c \
		run_export.c \
		run_unset.c \
		run_exit.c \
		print_export.c \
		add_to_export.c \
		build_in_utils.c \
		run_pipes.c \
		get_next_line/get_next_line.c \
		parser_escape.c \
		parser_pipecase.c \
		parser_quotes.c \
		parser_semicolon.c \
		parser_utils.c \
		parser.c \
		preparser.c \
		parser_redirect.c \
		handler_utils.c \
		sig_handler.c \
		cd_helper.c \
		error_handler.c \
		parser_dollar.c \
		get_path.c \
		main_utils.c \
		parser_dollar_utils.c \
		parser_redirect_utils.c \
		parser_redirect_to.c \
		parser_redirect_from.c \
		parser_parse_arg.c \
		parser_functions.c

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

INCLUDES = -I.

OBJS	= ${SRCS:.c=.o}

${NAME}:	${OBJS}
			$(MAKE) bonus -C ./libft
			${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${LIBFT} ${READLINE_LIB} -o $(NAME)

all:		${NAME}

clean:
			$(MAKE) clean -C ./libft
			rm -f ${OBJS}
			rm -f .redirection.txt

fclean:		clean 
			$(MAKE) fclean -C ./libft
			rm -f ${NAME}
			rm -f norminette_log.txt

re:			fclean all

norme:
	norminette ./libft/*.c ./*.h ${SRCS} > norminette_log.txt

.PHONY:		all clean fclean re bonus