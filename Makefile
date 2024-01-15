SRC_DIR	= src
INC_DIR	= header

SRCS	= $(SRC_DIR)/main.c $(SRC_DIR)/clean_data.c $(SRC_DIR)/ft_split.c \
		  $(SRC_DIR)/ft_strcmp.c $(SRC_DIR)/ft_strcpy.c $(SRC_DIR)/ft_strlen.c \
		  $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/utils_tab_node.c \
		  $(SRC_DIR)/check_node.c $(SRC_DIR)/get_type.c $(SRC_DIR)/utils_lc.c \
		  $(SRC_DIR)/display_env_list.c $(SRC_DIR)/create_env_tab.c \
		  $(SRC_DIR)/env_var_exist.c $(SRC_DIR)/expand_or_not.c \
		  $(SRC_DIR)/env_var_value.c $(SRC_DIR)/ft_strdup.c \
		  $(SRC_DIR)/lexer_check.c $(SRC_DIR)/init_tabint.c \
		  $(SRC_DIR)/utils_char.c $(SRC_DIR)/init_data.c \
		  $(SRC_DIR)/handle_redir.c $(SRC_DIR)/extract_cmd.c \
		  $(SRC_DIR)/check_path.c $(SRC_DIR)/find_path.c \
		  $(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/simple_split.c \
		  $(SRC_DIR)/exec.c $(SRC_DIR)/pipeline.c $(SRC_DIR)/builtin.c \
		  $(SRC_DIR)/ft_exit.c $(SRC_DIR)/ft_put.c $(SRC_DIR)/ft_echo.c \
		  $(SRC_DIR)/ft_env.c $(SRC_DIR)/ft_unset.c $(SRC_DIR)/ft_export.c \
		  $(SRC_DIR)/ft_cd.c $(SRC_DIR)/ft_pwd.c $(SRC_DIR)/ft_itoa.c \
		  $(SRC_DIR)/heredoc.c $(SRC_DIR)/sort_env_tab.c \
		  $(SRC_DIR)/error_mess.c $(SRC_DIR)/exit_and_clean.c \
		  $(SRC_DIR)/check_env_var.c $(SRC_DIR)/compute_cmd_size.c \
		  $(SRC_DIR)/split_cmd.c $(SRC_DIR)/update_var.c \
		  $(SRC_DIR)/extract_env_var.c $(SRC_DIR)/str_quote.c \
		  $(SRC_DIR)/ft_strdup_quote.c $(SRC_DIR)/other_strdup.c \
		  $(SRC_DIR)/check_file.c $(SRC_DIR)/exec_built.c \
		  $(SRC_DIR)/init_pipe.c $(SRC_DIR)/sub_pipeline.c \
		  $(SRC_DIR)/remove_quote.c $(SRC_DIR)/pipe_point.c

OBJS	= ${SRCS:.c=.o}
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3 -I $(INC_DIR)
NAME	= minishell

${NAME}: ${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline
all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all
