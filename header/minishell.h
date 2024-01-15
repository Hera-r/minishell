#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>

#define SUCCESS 0
#define FAIL 1
#define MISUSE 2
#define PERM_DENY 126
#define CMD_NOT_FOUND 127
#define CTRL_C 130

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define IN_QUOTE 42
#define OUT_QUOTE -42

#define BUFFER_SIZE 1050

#define MAX_EXIT 9223372036854775807
#define MIN_EXIT -9223372036854775807
#define MAX_LONG 19

#define SYNTAX_ERROR "syntax error near unexpected token"
#define UNCLOSED_ERROR "syntax error unclosed quote"
#define CHEVRON1 " « "
#define CHEVRON2 " » "

typedef enum e_token_type {
  T_STR,
  T_REDIR_OUT,
  T_REDIR_IN,
  T_HEREDOC,
  T_REDIR_OUT_APPEND,
  T_PIPE,
  T_ERROR,
  T_STR_REDIR,
} t_token_type;

typedef struct s_node {
  int type;
  char *token;
} t_node;

typedef struct s_child_pid {
  pid_t pid;
  struct s_child_pid *next;
} t_child_pid;

typedef struct s_var_env {
  char *name;
  char *value;
  struct s_var_env *next;
} t_var_env;

typedef struct s_tabint {
  int i;
  int start;
  int index;
  int status;
} t_tabint;

typedef struct s_quote {
  int status;
  int size;
  char value;
} t_quote;

typedef struct s_range {
  int start;
  int end;
  int i;
} t_range;

typedef struct s_data {
  struct s_node **node_tab;
  struct s_var_env *env_list;
  struct s_child_pid *pid_list;
  char **env_tab;
  int size;
  int nb_cmd;
  int nb_pipe;
  int nb_redir_in;
  int nb_redir_out;
  int output_fd;
  int input_fd;
  int index;
  int start_cmd;
  int ret;
  int last;
  int exit;
  int pipe_0;
  struct termios saved_attributes;
} t_data;

char *env_loop(char **envp, char *cmd);
char *extract_name(char *cmd);
char *extract_value(char *cmd, char *name);
char *ft_itoa(int nb);
char *ft_strcpy(char *dest, char *src, int start, int end);
char *ft_strdup(char *src, int start, int end);
char *ft_strdup_quote(char *src, int start, int end);
char *ft_strdup_split(char *src, int start, int end);
char *ft_strjoin(char *s1, char *s2);
char *ft_strjoin_classic(char *s1, char *s2);
char *process_path(char *cmd, char **envp);
char *remove_quote(char *cmd);
char *simple_strdup(char *s);
char *take_value(t_var_env *env_list, char *name);

char **extract_cmd(t_data *data);
char **from_list_to_tab(t_var_env *env_list);
char **ft_split(char *str);
char **simple_split(char *s, char c);
char **split_cmd(t_data *data, t_node **n_tab);

int append_heredoc(char *delim, t_data *data, int (*pipefd)[2]);
int append_list(t_data *data, char *var);
int builtin_list(t_data *data, char **cmd);
int builtin_parent(t_data *data, char **cmd);
int change_status_or_not(int status);
int check_error_node(t_node **node_tab, int size, t_data *data);
int check_env_var(t_node **node_tab, int size, t_var_env **env_list,
                  t_data *data);
int check_unclosed_double(char *cmd);
int check_unclosed_single(char *cmd);
int compute_size_cmd(t_data *data, t_node **node_tab);
int count_redir_cmd(t_data *data, t_node *node_tab);
int empty_cmd(t_data *data);
int err_msg(char *error, char *str, int code_error);
int exec_builtin(t_data *data, char **args, int (*pipefd)[2]);
int exec_cmd(char *path, char **args, t_data *data);
int expand_or_empty(t_node **node_tab, int index, t_var_env **env_list,
                    t_data *data);
int expand_var(t_node **node_tab, int index, char *value, int name_size);
int ft_cd(t_data *data, char **cmd);
int ft_echo(char **tab);
int ft_env(t_data *data, char **cmd);
int ft_exit(t_data *data, char **cmd);
int ft_export(t_data *data, char **cmd);
int ft_pwd(char **cmd);
int ft_size_env_list(t_var_env *env_list);
int ft_strcmp(const char *s1, const char *s2);
int ft_strlen(char *tab);
int ft_strlen_tab(char **tab);
int ft_unset(t_data *data, char **cmd);
int get_index_equal(char *var);
int get_node_id_pipe(t_node **node_tab, int size);
int get_node_id_redir(t_node **node_tab, int size);
int handle_pipeline(t_data *data);
int handle_redir(t_data *data, t_node *node_tab, int (*pipefd)[2]);
int has_env_var(char *token);
int has_plus_equal(char *cmd);
int init_env_list(t_data *data, char **envp);
int is_alpha(char c);
int is_builtin(char *cmd);
int is_digit(char c);
int is_directory(char *cmd);
int is_dir_or_cmdnotfound(char *path);
int is_double_quote(char *str, int start);
int is_empty_cmd(char *cmd);
int is_heredoc_node(t_node node);
int is_redir_node(t_node node);
int is_separators(char c);
int is_single_quote(char *str, int start, int end);
int is_space(char c);
int is_str(t_node node);
int is_str_double_quoted(t_node node);
int is_str_single_quoted(t_node node);
int is_str_quoted(char *str, int start, int end);
int is_valid_char(char c);
int is_valid_option(char *builtin, char *cmd);
int parser(t_node **node_tab, int size, t_var_env **env_list, t_data *data);
int size_without_quote(char *cmd);
int start_handle_pipe(t_data *data, int (**pipefd)[2]);
int sub_again_pipe(t_data *data, char ***result, int *i, int (*pipefd)[2]);
int udpate_env_var_value(t_data *data, char *var_name, char *new);
int var_exist(t_var_env *env_list, char *var_name);

t_node check_pipe(char *cmd);
t_node check_redir(char *cmd);
t_node check_str(char *cmd);

t_node *lexer(char **cmd_tab);

void append_pid(t_data *data, pid_t pid);
void check_file(char const *file, int i);
void check_pipe_node(t_node **node_tab, int size);
void check_redir_node(t_node **node_tab, int size);
void clean_child(t_data *data, char **args, int (*pipefd)[2]);
void clean_node_error(t_node **node_tab, int size);
void del_env_var(t_data *data, char *name_del);
void display_env_list(t_var_env *env_list);
void display_error(char *cmd, char *builtin);
void display_error_dir(char *cmd);
void display_sort_env(t_data *data);
void end_loop_pipe(t_data *data, char ***result, int *i, int (*pipefd)[2]);
void exit_point(t_data *data, char ***result);
void final_clean(t_data *data);
void free_all(char **content);
void free_env_list(t_data *data);
void free_node_t(t_node **node_tab, int size);
void free_node_tab(t_data *data);
void free_pid_list(t_child_pid *pid_list);
void free_pipefd(int (*pipefd)[2], int size);
void free_simple_node(t_node *node_tab, int size);
void ft_putstr_fd(char *str, int fd);
void ft_putstr_nl_fd(char *str, int fd);
void handle_point(t_data *data, char ***result);
void handle_signals(int signo);
void init_data(t_data *data, t_node **node_tab, int size);
void init_data_split(t_tabint *tab, int *node, t_data *data);
void init_first_pipe(t_data *data, int (*pipefd)[2], int i);
void init_pipe_data(int *i, char **path, char ***result, int (**pipefd)[2]);
void init_size(int *size, char ***result);
void init_tab(t_tabint *tab);
void modif_param(char *c, char value, int *status);
void sort_env_tab(char **env_tab);
void sub_else_pipe(t_data *data, char ***result, char **path, int (*pipefd)[2]);
void sub_exec_pipe(t_data *data, char ***result, char **path);
void update_data(char *c, char value, t_tabint *tab);
void update_param(t_quote *quote, char value);
void update_quote(char *c, char value, t_tabint *tab);

extern int g_received_signal;
#endif