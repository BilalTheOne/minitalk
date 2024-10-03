#include "../minishell.h"

void	true_v1(t_command *cmd, t_env **head, int n)
{
	(void)head;
	(void)n;
	if (cmd->exit_status == 1)
		*((unsigned char *)exit_status()) = 1;
	else
		*((unsigned char *)exit_status()) = 0;
}

void pwd(t_command *cmd, t_env **head, int n)
{
	(void)head;
	int fd = 1;
	(void)n;
	char arr[PATH_MAX];
	if (cmd->fd_out > 0 && cmd->fd_out != 1)
		fd = cmd->fd_out;
	getcwd(arr, PATH_MAX); //free this
	ft_putstr_fd(arr, fd);
	ft_putstr_fd("\n", fd);
	*((unsigned char *)exit_status()) = 0;
}