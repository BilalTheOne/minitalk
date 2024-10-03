#include "../minishell.h"

void	cd(t_command *cmd, t_env **head, int n)
{
	int a = 0;
	(void)n;
	char *path = cmd->args2[1];
	char arr[PATH_MAX];
	char *home = NULL;
	char *cwd = getcwd(0, 0);
	if (path == NULL)
	{
		home = get_env_value(*head, "HOME");
		if (home == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			*((unsigned char *)exit_status()) = 1;
		}
		else
			chdir(get_env_value(*head, "HOME"));
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		home = get_env_value(*head, "OLDPWD");
		if (home == NULL)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			*((unsigned char *)exit_status()) = 1;
		}
		else
		{
			ft_putstr_fd(get_env_value(*head, "OLDPWD"), 1);
			ft_putstr_fd("\n", 1);
			chdir(get_env_value(*head, "OLDPWD"));
		}
	}
	else if ((chdir(path) == -1 || cwd == NULL) && ft_strcmp(path, ""))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		*((unsigned char *)exit_status()) = 1;
		a = 1;
	}
	getcwd(arr, PATH_MAX);
	update_env_var(*head, "OLDPWD", get_env_value(*head, "PWD"), 1);
	update_env_var(*head, "PWD", arr, 1);
	free(cwd);
	if (a == 0)
		*((unsigned char *)exit_status()) = 0;
}
