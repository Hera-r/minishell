#include "../header/minishell.h"

void ft_ctrl_c_exit(int i) {
  (void)i;
  exit(1);
}

void clean_heredoc(t_data *data, int (*pfd)[2]) {
  int i;

  i = 0;
  free_pid_list(data->pid_list);
  data->pid_list = NULL;
  free_env_list(data);
  data->env_list = NULL;
  if (data->node_tab) {
    free_node_tab(data);
    data->node_tab = NULL;
  }
  free_all(data->env_tab);
  close((*data).input_fd);
  close((*data).output_fd);
  while (i < (data->nb_cmd - 1)) {
    close(pfd[i][0]);
    close(pfd[i][1]);
    i++;
  }
  free_pipefd(pfd, (data->nb_cmd - 1));
}

static void w_rl_to_pipe(int pipefd[2], char *del, t_data *data,
                         int (*pfd)[2]) {
  char *next_line;
  int len_next_line;

  signal(SIGINT, &ft_ctrl_c_exit);
  close(pipefd[0]);
  next_line = readline("> ");
  len_next_line = ft_strlen(next_line);
  while (next_line && ft_strcmp(next_line, del) != SUCCESS) {
    if (write(pipefd[1], next_line, len_next_line) == -1)
      perror(NULL);
    if (write(pipefd[1], "\n", 1) == -1)
      perror(NULL);
    free(next_line);
    next_line = readline("> ");
    len_next_line = ft_strlen(next_line);
  }
  free(next_line);
  close(pipefd[1]);
  clean_heredoc(data, pfd);
  exit(SUCCESS);
}

int append_heredoc(char *delimiter, t_data *data, int (*pfd)[2]) {
  int pipefd[2];
  pid_t pid;
  int exit_status;

  if (pipe(pipefd) == -1) {
    perror(NULL);
    return (-1);
  }
  pid = fork();
  if (pid == -1) {
    perror(NULL);
    close(pipefd[1]);
    close(pipefd[0]);
    return (-1);
  }
  if (pid == 0) {
    w_rl_to_pipe(pipefd, delimiter, data, pfd);
    return (pipefd[0]);
  }
  waitpid(pid, &exit_status, 0);
  close(pipefd[1]);
  return (pipefd[0]);
}
