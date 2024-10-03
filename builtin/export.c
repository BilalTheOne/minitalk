#include "../minishell.h"

char **env_to_array(t_env *head)
{
	int count = 0;
	delete_env_var(&head, "?");
	t_env *current = head;
	while (current != NULL) 
	{
		count++;
		current = current->next;
	}
	char **env_array = (char **)ft_malloc((count + 1) * sizeof(char *), 0);
	if (!env_array)
		return (NULL);
	current = head;
	int i = 0;
	while (current != NULL) 
	{
		env_array[i] = (char *)ft_malloc(ft_strlen(current->key) + ft_strlen(current->value) + 2, 0);
		if (!env_array[i])
			return (NULL);
		ft_strcpy(env_array[i], current->key);
		if (current->equal == 1)
			ft_strcat(env_array[i], "=");
		ft_strcat(env_array[i], current->value);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	add_to_env(&head, "?", ft_itoa(*((unsigned char *)exit_status())), 2);
	return (env_array);
}

void env_sorting(t_env *head, t_command *cmd)
{
	int fd = 1;
	if (cmd->fd_out > 0 && cmd->fd_out != 1)
		fd = cmd->fd_out;
	char **env_array = env_to_array(head);
	int i = 0;
	while (env_array[i] != NULL)
	{
		int j = i + 1;
		while (env_array[j] != NULL)
		{
			if (ft_strcmp(env_array[i], env_array[j]) > 0)
			{
				char *temp = env_array[i];
				env_array[i] = env_array[j];
				env_array[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	int first = 1;
	while (env_array[i] != NULL)
	{
		first = 0;
		ft_putstr_fd("declare -x ", fd);
		while(*env_array[i] != '\0')
		{
			if (*env_array[i] == '=' && first == 0)
			{
				ft_putstr_fd("=\"", fd);
				first = 1;
			}
			else
				ft_putchar_fd(*env_array[i], fd);
			env_array[i]++;
		}
		if (first == 1)
			ft_putstr_fd("\"", fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
	*((unsigned char *)exit_status()) = 0;
}

int   if_minus_plus(char **arg)
{
    if (arg[1] == NULL) {
        return 0;
    }

    char *minus = ft_strnstr(arg[1], "-=", ft_strlen(arg[1]));
    if (minus != NULL)
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(arg[1], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        *((unsigned char *)exit_status()) = 1;
        return (1);
    }
    return (0);
}

int  if_symbol(char **args)
{
	int i = 1;
	int j;
	while (args[i])
	{
		char *delimiter_position = ft_strchr(args[i], '=');
		char *plus_equal = ft_strnstr(args[i], "+=", ft_strlen(args[i]));
		if (ft_strncmp(args[i], "=", 1) == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*((unsigned char *)exit_status()) = 1;
			return (1);
		}
		if (delimiter_position != NULL && plus_equal == NULL)
		{
			char *temp_env_var = ft_strdup(args[i]);
			temp_env_var[delimiter_position - args[i]] = '\0';
			j = 0;
			while (temp_env_var[j])
			{
				if (ft_isalnum(temp_env_var[j]) == 0 && temp_env_var[j] != '_')
				{
					ft_putstr_fd("minishell: export: `", 2);
					ft_putstr_fd(args[i], 2);
					ft_putstr_fd("': not a valid identifier\n", 2);
					*((unsigned char *)exit_status()) = 1;
					return (1);
				}
				j++;
			}
		}
		else if (plus_equal != NULL && delimiter_position != NULL)
		{
			char *temp_env_var = ft_strdup(args[i]);
			temp_env_var[plus_equal - args[i]] = '\0';
			j = 0;
			while (temp_env_var[j])
			{
				if (ft_isalnum(temp_env_var[j]) == 0 && temp_env_var[j] != '_')
				{
					ft_putstr_fd("minishell: export: `", 2);
					ft_putstr_fd(args[i], 2);
					ft_putstr_fd("': not a valid identifier\n", 2);
					*((unsigned char *)exit_status()) = 1;
					return (1);
				}
				j++;
			}
		}
		else 
		{
			j = 0;
			while (args[i][j])
			{
				if (ft_isalnum(args[i][j]) == 0 && args[i][j] != '_')
				{
					ft_putstr_fd("minishell: export: `", 2);
					ft_putstr_fd(args[i], 2);
					ft_putstr_fd("': not a valid identifier\n", 2);
					*((unsigned char *)exit_status()) = 1;
					return (1);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

int export_parsing(t_command *cmd)
{
    int i = 1;
    if(cmd->args2 != NULL && cmd->args2[i] != NULL && ft_isdigit(cmd->args2[i][0]))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(cmd->args2[i], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        *((unsigned char *)exit_status()) = 1;
        return (1);
    }
    if (cmd->args2 != NULL && cmd->args2[i] != NULL && cmd->args2[i][0] == '=' && cmd->args2[i][1] == '\0')
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(cmd->args2[i], 2);
        ft_putstr_fd("': not a valid identifier\n", 2);
        *((unsigned char *)exit_status()) = 1;
        return (1);
    }
    if (if_minus_plus(cmd->args2))
        return (1);
    if (if_symbol(cmd->args2))
        return (1);
    return (0);
}

void export_built(t_command *cmd, t_env **head, int n)
{
	int i = 1;
	int fd = 1;
	(void)n;
	if (cmd->args2[1] == NULL)
	{
		env_sorting(*head, cmd);
		return ;
	}
	if (export_parsing(cmd))
		return ;
	if (cmd->fd_out > 0 && cmd->fd_out != 1)
		fd = cmd->fd_out;
	while (cmd->args2[i])
	{
		char *delimiter_position = ft_strchr(cmd->args2[i], '=');
		char *plus_equal = ft_strnstr(cmd->args2[i], "+=", ft_strlen(cmd->args2[i]));
		if (delimiter_position != NULL && plus_equal == NULL) 
		{
			char *temp_env_var = ft_strdup(cmd->args2[i]);
			temp_env_var[delimiter_position - cmd->args2[i]] = '\0';
			if (get_env_value(*head, temp_env_var) == NULL && plus_equal == NULL)
				add_to_env(head, temp_env_var, delimiter_position + 1, 1);
			else
				update_env_var(*head, temp_env_var, delimiter_position + 1, 1);
		}
		else if (plus_equal != NULL)
		{
			char *temp_env_var;
			temp_env_var = ft_strdup(cmd->args2[i]);
			temp_env_var[plus_equal - cmd->args2[i]] = '\0';
			if (get_env_value(*head, temp_env_var) == NULL)
				add_to_env(head, temp_env_var, plus_equal + 2, 1);
			else
			{
				char *temp = ft_strdup(plus_equal + 2);
				char *temp2 = ft_strjoin(get_env_value(*head, temp_env_var), temp);
				update_env_var(*head, temp_env_var, temp2, 1);
			}
		}
		else 
		{
			if (get_env_value(*head, cmd->args2[i]) == NULL)
				add_to_env(head, cmd->args2[i], "", 0);    
		}
		i++;
	}
	*((unsigned char *)exit_status()) = 0;
}
