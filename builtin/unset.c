#include "../minishell.h"

int unset_parsing(char *s)
{
	int i = 0;
	if (ft_isdigit(s[i]) || ft_strcmp(s, "") == 0)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*((unsigned char *)exit_status()) = 1;
		return (1);
	}
	while (s[i])
	{
		if (ft_isdigit(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
			i++;
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(s, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*((unsigned char *)exit_status()) = 1;
			return (1);
		}
	}
	return (0);
}

void unset(t_command *cmd, t_env **head, int n)
{
	int i = 1;
	(void)n;
	while (cmd->args2[i])
	{
		if (unset_parsing(cmd->args2[i]) == 1)
		{
			*((unsigned char *)exit_status()) = 1;
			return ;
		}
		i++;
	}
	i = 1;
	while (cmd->args2[i])
	{
		delete_env_var(head, cmd->args2[i]);
		i++;
	}
	*((unsigned char *)exit_status()) = 0;
}