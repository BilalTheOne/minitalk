#include "../minishell.h"

int check_n(char *str)
{
	int i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] == 'n')
			i++;
		else
			return (0);
	}
	return (i);
}

void echo_built(t_command *cmd, t_env **head, int i)
{
	int j = 0;
	int check = 0;
	int newline = 1;
	int fd = 1;
	i = 1;
	(void)head;
	if (cmd->fd_out > 0 && cmd->fd_out != 1)
		fd = cmd->fd_out;
	while (cmd->args2[i])
	{
		j = 0;
		if (check_n(cmd->args2[i]) == (int)ft_strlen(cmd->args2[i]) && check == 0)
		{
			newline = 0;
			i++;
		}
		else {
			check = 1;
			while (cmd->args2[i][j])
			{
				ft_putchar_fd(cmd->args2[i][j], fd);
				j++;
			}
			if (cmd->args2[i + 1])
				ft_putchar_fd(' ', fd);
			i++;
		}
	}
	if (newline || ft_strcmp(cmd->args2[1], "") == 0)
		ft_putchar_fd('\n', fd);
	*((unsigned char *)exit_status()) = 0;
}
