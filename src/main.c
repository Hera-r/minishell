#include "../header/minishell.h"

int g_received_signal;

void handle_signals(int signo) {
  g_received_signal = signo;
  if (g_received_signal == SIGINT) {
    ft_putstr_fd("\n", STDOUT);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_received_signal = 0;
  }
}

void init_minishell(t_data *data, char ***result, t_node **node_tab) {
  struct termios new_attributes;

  tcgetattr(STDIN_FILENO, &(*data).saved_attributes);
  signal(SIGINT, handle_signals);
  signal(SIGQUIT, SIG_IGN);
  new_attributes = (*data).saved_attributes;
  new_attributes.c_lflag &= ~ECHOCTL;
  tcsetattr(STDIN_FILENO, TCSANOW, &new_attributes);
  *result = NULL;
  (*data).ret = SUCCESS;
  (*data).exit = FAIL;
  (*data).env_list = NULL;
  (*data).env_tab = NULL;
  (*data).node_tab = NULL;
  *node_tab = NULL;
}

int sub_mini_loop(t_data *data, char ***result, char **buf, t_node **node_tab) {
  *buf = readline("minishell> ");
  if (*buf == NULL) {
    final_clean(data);
    ft_putstr_nl_fd("exit", STDOUT);
    exit(0);
  }
  *result = ft_split(*buf);
  if (!*result)
    return (free(*buf), FAIL);
  add_history(*buf);
  free(*buf);
  *buf = NULL;
  *node_tab = lexer(*result);
  if (!*node_tab)
    return (FAIL);
  return (SUCCESS);
}

int minishell_loop(t_data *data, char **result, char **buffer,
                   t_node *node_tab) {
  int size;

  while ((*data).exit == FAIL) {
    if (sub_mini_loop(data, &result, buffer, &node_tab) == FAIL)
      return (FAIL);
    init_size(&size, &result);
    if (parser(&node_tab, size, &(*data).env_list, data) == SUCCESS) {
      init_data(data, &node_tab, size);
      (*data).env_tab = from_list_to_tab((*data).env_list);
      if (handle_pipeline(data) == FAIL)
        return (FAIL);
      wait(NULL);
    } else {
      free_node_t(&node_tab, size);
      node_tab = NULL;
    }
    rl_on_new_line();
    signal(SIGINT, handle_signals);
  }
  return (SUCCESS);
}

int main(int argc, char *argv[], char *envp[]) {
  char *buffer;
  char **result;
  t_node *node_tab;
  t_data data;
  int ret;

  (void)argv;
  memset(&data, 0, sizeof(t_data));
  if (argc == 1) {
    g_received_signal = 0;
    init_minishell(&data, &result, &node_tab);
    init_env_list(&data, envp);
    if (minishell_loop(&data, result, &buffer, node_tab) == FAIL)
      return (FAIL);
    ret = data.ret;
    final_clean(&data);
    return (ret);
  }
  ft_putstr_nl_fd("No argument needed to execute minishell", STDOUT);
  return (SUCCESS);
}
