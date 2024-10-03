/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 01:25:05 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/30 17:44:39 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int g_signal = 0;

void	*exit_status()
{
    static int status = 0;
    return (&status);
}

char* construct_command(char *path, char *arg)
{
	if (path == NULL || arg == NULL)
		return (NULL);
	char *command = ft_malloc(ft_strlen(path) + ft_strlen(arg) + 2, 0);
	if (!command)
		return (NULL);
	ft_strcpy(command, path);
	ft_strcat(command, "/");
	ft_strcat(command, arg);
	return (command);
}

t_env *new_node(char *env_var)
{
	t_env *node = ft_malloc(sizeof(t_env), 0);
	if (!node)
		return (NULL);
	char *delimiter_position = ft_strchr(env_var, '=');
	char *temp_env_var = ft_strdup(env_var);
	if (!node || !delimiter_position || !temp_env_var)
		return (NULL);
	temp_env_var[delimiter_position - env_var] = '\0';
	node->key = ft_strdup(temp_env_var);
	if (!node->key)
		return (NULL);
	node->value = ft_strdup(delimiter_position + 1);
	node->equal = 1;
	node->next = NULL;
	return (node);
}

int   have_slash(char *s)
{
	int i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char *check_command(char **path_split, char **av)
{
	int i = 0;
	char *check = NULL;
	while (path_split[i])
	{
		if (have_slash(av[0]) == 1)
		{
			check = ft_strdup(av[0]);
			if (!check)
				return (NULL);
		}
		else
		{
			check = construct_command(path_split[i], av[0]);
			if (access(check, F_OK) == 0)
				break ;
		}
		i++;
	}
	return (check);
}

void handle_sigint(int sig) 
{
    if (sig == SIGINT)
    {
		rl_on_new_line();
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_redisplay();
    }
    if (sig == SIGQUIT)
    {
        if (waitpid(-1, NULL, SIGQUIT) == 0)
        {
            ft_putstr_fd("Quit: 3\n", 1);
            return ;
        }
    }
}

void setup_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
}

void setup_env(char **envp, t_env **head, t_env **current)
{
	int i = 0;
	while (envp[i] != NULL) 
	{
		if (*head == NULL) 
		{
			*head = new_node(envp[i]);
			*current = *head;
		} 
		else 
		{
			(*current)->next = new_node(envp[i]);
			*current = (*current)->next;
		}
		i++;
	}
}

void	status_a(int status)
{
	if (status == 127 || status == 126 || status == 0 || status == 1)
	{
		*((unsigned char *)exit_status()) = status;
		return ;
	}
	if (status == 13)
	{
		*((unsigned char *)exit_status()) = 0;
		return ;
	}
    if (WIFSIGNALED(status))
        *((unsigned char *)exit_status()) = WTERMSIG(status) + 128;
    else if (WEXITSTATUS(status))
		*((unsigned char *)exit_status()) = WEXITSTATUS(status);
}

void process_commands(t_env **head, int *status)
{
	char *s;
	struct termios term;
	tcgetattr(0, &term);
	while (1)
	{
		*status = *(unsigned char *)exit_status();
		*(unsigned char *)exit_status() = 0;
		s = readline("minishell$ ");
		if (s == NULL)
			break ;
		add_history(s);
		t_command *cmd = parsing(s, *head);
		int a = 0;
		if (cmd == NULL)
		{
			if (*(unsigned char *)exit_status() == 2)
				update_env_var(*head, "?", "258", 2);
			if (*(unsigned char *)exit_status() == 1)
				update_env_var(*head, "?", "1", 2);
			if (*(unsigned char *)exit_status() == 0)	
				update_env_var(*head, "?", "0", 2);
			a = 1;
			free(s);
			continue ;
		}	
		if (ft_strcmp(execute(head, cmd), "done") == 0 && a == 0)
			update_env_var(*head, "?", ft_itoa(*(unsigned char *)exit_status()), 2);
		tcsetattr(0, TCSANOW, &term);
		ft_fds();
		free(s);
	}
}

void add_to_envs(t_env **head)
{
	char *path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	char *shlvl = "0";
	char *pwd = getcwd(NULL, 0);
	add_to_env(head, "PATH", path, 2);
	add_to_env(head, "_", "minishell", 1);
	add_to_env(head, "SHLVL", shlvl, 1);
	add_to_env(head, "PWD", pwd, 1);
	add_to_env(head, "OLDPWD", "", 0);
	add_to_env(head, "?", ft_strdup(ft_itoa(0)), 2);
	free(pwd);
}

int main(int ac, char **av, char **envp)
{
	int status = 0;
	(void)ac;
	(void)av;
	int shlvl = 0;
	t_env *head = NULL;
	t_env *current = NULL;
	// if (!isatty(0))
	// {
	// 	ft_putstr_fd("minishell: is not a tty\n", 2);
	// 	exit(2);
	// }
	rl_catch_signals = 0;
	setup_signals();
	if (*envp == NULL)
		add_to_envs(&head);
	else
		setup_env(envp, &head, &current);
	if (get_env_value(head, "?") == NULL)
		add_to_env(&head, "?", "0", 2);
	shlvl = ft_atoi(get_env_value(head, "SHLVL")) + 1;
	if (shlvl < 0)
		shlvl = 0;
	if (shlvl > 999)
		update_env_var(head, "SHLVL", "", 1);
	else
		update_env_var(head, "SHLVL", ft_itoa(shlvl), 1);
	update_env_var(head, "OLDPWD", "", 0);
	process_commands(&head, &status);
	ft_malloc(0, 1);
	ft_putstr_fd("exit\n", 1);
	return (status);
}
