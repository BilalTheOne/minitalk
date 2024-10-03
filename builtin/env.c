#include "../minishell.h"

void add_to_env(t_env **head, char *key, char *value, int equal)
{
	t_env *new_env = ft_malloc(sizeof(t_env), 0);
	new_env->key = ft_malloc(ft_strlen(key) + 1, 0);
	new_env->value = ft_malloc(ft_strlen(value) + 1, 0);
	ft_strcpy(new_env->key, key);
	new_env->equal = equal;
	ft_strcpy(new_env->value, value);
	new_env->next = NULL;
	ft_lstadd_back(head, new_env);
}

void update_env_var(t_env *head, char *key, char *new_value, int equal)
{
	t_env *current = head;
	while (current != NULL) 
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->value = ft_malloc(ft_strlen(new_value) + 1, 0);
			if (!current->value)
				return ;
			ft_strcpy(current->value, new_value);
			current->equal = equal;
			break;
		}
		current = current->next;
	}
}

char *get_env_value(t_env *head, char *key)
{
	t_env *current = head;
	while (current != NULL) 
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void    delete_env_var(t_env **head, char *key)
{
    t_env *current = *head;
    t_env *prev = NULL;
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (prev == NULL)
                *head = current->next;
            else
                prev->next = current->next;
            break;
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

void    env(t_command *cmd, t_env **head, int n)
{
	t_env *current = *head;
	(void)n;
	int fd = 1;
	if (cmd->fd_out > 0 && cmd->fd_out != 1)
		fd = cmd->fd_out;
	while (current != NULL) 
	{
		if (current->equal == 1)
		{
			ft_putstr_fd(current->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(current->value, fd);
			ft_putstr_fd("\n", fd);
		}
		current = current->next;
	}
	*((unsigned char *)exit_status()) = 0;
}