/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:54:33 by ohaida            #+#    #+#             */
/*   Updated: 2024/09/30 19:18:46 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_list(t_env **head, t_env **current)
{
	int	count;

	count = 0;
	delete_env_var(head, "?");
	*current = *head;
	while (*current != NULL)
	{
		count++;
		if ((*current)->equal == 0 || (*current)->equal == 2)
		{
			delete_env_var(head, (*current)->key);
			count--;
		}
		*current = (*current)->next;
	}
	return (count);
}

char	**fill_env_array(t_env *head, int count)
{
	t_env	*current;
	char	**env_array;
	int		i; 

	current = head;
	env_array = (char **)ft_malloc((count + 1) * sizeof(char *), 0);
	if (!env_array)
		return (NULL);
	i = 0;
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
	return (env_array);
}

char	**env_to_arr(t_env *head)
{
	t_env	*current;
	int		count;

	count = size_of_list(&head, &current);
	return (fill_env_array(head, count));
}

char	*ft_tolower(char *str)
{
	char	*s;
	int		i;

	s = ft_strdup(str);
	if (!s)
		return (NULL);
	i = 0;
	while (s[i] >= 'A' && s[i] <= 'Z')
	{
		s[i] = s[i] + 32;
		i++;
	}
	return (s);
}

int	builtns(t_command *cmd, t_env **head, int n)
{
	command_map	commands[8];
	size_t		i;

	commands[0] = (command_map){"exit", exit_bult};
	commands[1] = (command_map){"echo", echo_built};
	commands[2] = (command_map){"env", env};
	commands[3] = (command_map){"pwd", pwd};
	commands[4] = (command_map){"cd", cd};
	commands[5] = (command_map){"unset", unset};
	commands[6] = (command_map){"export", export_built};
	commands[7] = (command_map){"true", true_v1};
	if (!cmd || !head)
		return (0);
	i = 0;
	while (i < 8)
	{
		if (ft_strcmp(ft_tolower(cmd->args2[0]), commands[i].command) == 0)
		{
			commands[i].func(cmd, head, n);
			return (1);
		}
		i++;
	}
	return (0);
}

int	folder(char *command)
{
	struct stat		sb;

	if (stat(command, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

int check_null(char **args)
{
	if (**args == '\0')
		return (1);
	return (0);
}

void	error_exit(char **args, char *msg, int exit_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(msg, 2);
	args[0] = ft_strdup("true");
	*((unsigned char *)exit_status()) = exit_code;
	if (exit_code == 127)
		exit(127);
	if (exit_code == 126)
		exit(126);
}

void	check_errors(char **args, char *command)
{
	if (!access(command, F_OK))
		error_exit(args, ": Permission denied\n", 126);
	else if (have_slash(args[0]))
		error_exit(args, ": No such file or directory\n", 127);
	else if (access(command, F_OK) == -1 && ft_strcmp(command, NULL) != 0)
		error_exit(args, ": command not found\n", 127);
}

void	execute_command(char **args, char **path_split, t_env *head)
{
	int		i;
	char	*command;

	i = 0;
	signal(SIGINT, SIG_DFL);
	if (!ft_strcmp(args[0], ".") || !ft_strcmp(args[0], "..") || !ft_strcmp(args[0], ""))
		error_exit(args, ": command not found\n", 127);
	else
	{
		while (path_split[i])
		{
			command = check_command(path_split, args);
			if (folder(command) && !check_null(args))
				error_exit(args, ": is a directory\n", 126);
			if (!access(command, X_OK | F_OK))
			{
				execve(command, args, env_to_arr(head));
				exit(0);
			}
			check_errors(args, command);
			i++;
		}
	}
}

void	dup_fd(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->redirect > 0)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			exit(0);
	}
	if (cmd->dredirect > 0)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			exit(0);
	}
	if (cmd->append > 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			exit(0);
	}
	if (cmd->dappend > 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			exit(0);
	}
}

int	error_no(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	return (1);
}

void	one_command(t_command *cmd, char **path_split, t_env **head)
{
	int		status;
	pid_t	pid;

	if (path_split == NULL && builtns(cmd, head, 0) == 0)
	{
		error_no(cmd->args2[0]);
		*((unsigned char *)exit_status()) = 127;
	}
	else if (builtns(cmd, head, 0) == 0)
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			dup_fd(cmd);
			execute_command(&cmd->args2[0], path_split, *head);
			exit(0);
		}
		if (*(unsigned char *)exit_status() == 1)
			status_a(*(unsigned char *)exit_status());
		else
		{
			waitpid(pid, &status, 0);
			status_a(status);
		}
	}
}

void pipes(t_command *cmd, char **path_split, t_env **head)
{
    int pipe_fd[2];
    int in_fd = 0;
    pid_t pid;
    
    if (!cmd) {
        return;
    }
    while (cmd)
    {
        if (pipe_with_gc(pipe_fd) == -1) {
            perror("pipe");
            exit(1);
        }
        pid = fork();
        if (pid == -1) {
            perror("fork");
            *((unsigned char *)exit_status()) = 1;
			return ;
        }
        if (pid == 0)
        {
            if (in_fd != 0)
            {
                if (dup2(in_fd, STDIN_FILENO) == -1) {
                    perror("dup2");
                    exit(1);
                }
                if (close(in_fd) == -1) {
                    perror("close");
                    exit(1);
                }
            }
            if (cmd->next)
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
                    perror("dup2");
                    exit(1);
                }
            if (close(pipe_fd[0]) == -1 || close(pipe_fd[1]) == -1) {
                perror("close");
                exit(1);
            }
            dup_fd(cmd);
            if (path_split == NULL)
            {
                if (builtns(cmd, head, 1) != 1)
                {
                    if (folder(cmd->args2[0]) == 1)
                    {
                        ft_putstr_fd("minishell: ", 2);
                        ft_putstr_fd(cmd->args2[0], 2);
                        ft_putstr_fd(": is a directory\n", 2);
                    }
                    else
                    {
                        ft_putstr_fd("minishell: ", 2);
                        ft_putstr_fd(cmd->args2[0], 2);
                        ft_putstr_fd(": No such file or directory\n", 2);
                    }
                }
            }
            else
                if (builtns(cmd, head, 1) == 0)
                    execute_command(&cmd->args2[0], path_split, *head);
            	exit(*(unsigned char *)exit_status());
        }
        else
        {
            if (close(pipe_fd[1]) == -1) {
                perror("close");
                exit(1);
            }
            if (in_fd != 0)
                if (close(in_fd) == -1) {
                    perror("close");
                    exit(1);
                }
            in_fd = dup(pipe_fd[0]);
            if (in_fd == -1) {
                perror("dup");
                exit(1);
            }
            if (close(pipe_fd[0]) == -1) {
                perror("close");
                exit(1);
            }
        }
		if (cmd->pipe == 1)
			cmd = cmd->next;
		else
		 	break ;
        if (!cmd) {
            break;
        }
    }
}

int	len_list(t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	while (cmd)
	{
		if (cmd->pipe == 1)
		{
			i++;
			cmd = cmd->next;
		}
		else 
		{
			i++;
			break ;
		}
	}
	return (i);
}

char	*execute(t_env **head, t_command *cmd)
{
	char	*path;
	char	**path_split;
	int		length;
	int		status;

	if (!cmd || !cmd->args2[0] || len_list(cmd) == 0)
		return (NULL);
	path = get_env_value(*head, "PATH");
	if (path == NULL)
		path_split = NULL;
	else
		path_split = ft_split(path, ':');
	length = len_list(cmd);
	if (length == 1)
		one_command(cmd, path_split, head);
	else if (length >= 2)
	{
		pipes(cmd, path_split, head);
		t_command *current = ft_lstlast(cmd);
		if (!current)
			return (NULL);
		if (current->pipe == 0 && current->exit_status == 1)
			status_a(current->exit_status);
		else
		{
			while (waitpid(-1, &status, 0) != -1)
				;
			status_a(status);
		}
	}
	return (ft_strdup("done"));
}
