#include "../header/minishell.h"

void restore_terminal_attributes(struct termios *saved_attributes) {
  tcsetattr(STDIN_FILENO, TCSANOW, saved_attributes);
}

void display_env_tab(char **tab) {
  int i;

  i = 0;
  while (tab && tab[i]) {
    ft_putstr_nl_fd(tab[i], 1);
    free(tab[i]);
    i++;
  }
}

void final_clean(t_data *data) {
  free_pid_list(data->pid_list);
  data->pid_list = NULL;
  free_env_list(data);
  data->env_list = NULL;
  if (data->node_tab) {
    free_node_tab(data);
    data->node_tab = NULL;
  }
  free_all(data->env_tab);
  data->env_tab = NULL;
  if (data->input_fd > STDERR)
    close(data->input_fd);
  if (data->output_fd > STDERR)
    close(data->output_fd);
  restore_terminal_attributes(&data->saved_attributes);
  rl_free_line_state();
  rl_cleanup_after_signal();
  rl_clear_history();
}

void clean_child(t_data *data, char **args, int (*pipefd)[2]) {
  free_pid_list(data->pid_list);
  data->pid_list = NULL;
  free_env_list(data);
  data->env_list = NULL;
  if (args) {
    free_all(args);
    args = NULL;
  }
  if (data->node_tab) {
    free_node_tab(data);
    data->node_tab = NULL;
  }
  free_all(data->env_tab);
  close((*data).input_fd);
  close((*data).output_fd);
  free_pipefd(pipefd, (data->nb_cmd - 1));
}

void clean_node_error(t_node **node_tab, int size) {
  int i;

  i = 0;
  while (i < size) {
    if ((*node_tab)[i].token) {
      free((*node_tab)[i].token);
      (*node_tab)[i].token = NULL;
    }
    i++;
  }
}
