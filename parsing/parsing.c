/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:29:03 by bel-barb          #+#    #+#             */
/*   Updated: 2024/10/03 18:20:56 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdio.h>
#include <sys/unistd.h>

int count_token(char *s)
{
	int i = 0;
	int count = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
		{
			count++;
			if (s[i + 1] == '>' || s[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (count);
}

int quotes_validity(char *s)
{
	int i = 0;
	char quote;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			quote = s[i];
			i++;
			while (1)
			{
				if (s[i] == '\0')
					return (1);
				if (s[i] == quote)
					break;
				i++;
			}
		}
		i++;
	}
	return (0);
}

int check_parse(char **args)
{
    int i = 0;

    while (args[i])
    {
        if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0 ||
            ft_strcmp(args[i], "<") == 0 || ft_strcmp(args[i], "<<") == 0)
        {
            if (!args[i + 1] || ft_strcmp(args[i + 1], ">") == 0 ||
                ft_strcmp(args[i + 1], ">>") == 0 || ft_strcmp(args[i + 1], "<") == 0 ||
                ft_strcmp(args[i + 1], "<<") == 0)
                return (i);
        }
        i++;
    }
    return (-1);
}

void ft_error(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
}

int	ambiguous(char **args)
{
	int i;
	i = 0;
	while (args[i])
		i++;
	if (i != 1)
		return (1);
	return (0);
}

int calculate2(char **args, t_env *head)
{
	(void)head;
	int total_rows = 0;
	int z = 0;
	char **tmp;

	while (args[z])
	{
		if (args[z][0] == '$')
		{
			if (args[z][0] == '$' && args[z][1] == '"' && args[z][2] == '"')
			{
				total_rows++;
				break ;
			}
			tmp = ft_split(expand(args[z], head), ' ');
			int v = 0;
			while (tmp[v])
			{
				total_rows++;
				v++;
			}
			z++;
		}
		else
		{
			total_rows++;
			z++;
		}
	}
	return (total_rows);
}

int is_dollar_inside_quotes(char *str) 
{
    int inside_quotes = 0;
    int i = 0;

    while (str[i] != '\0') 
	{
        if (str[i] == '"' && inside_quotes == 0)
            inside_quotes = 2;
		else if (str[i] == '"' && inside_quotes == 2)
            inside_quotes = 0;
        else if (str[i] == '\'' && inside_quotes == 0)
            inside_quotes = 1;
        else if (str[i] == '\'' && inside_quotes == 1)
            inside_quotes = 0;
        else if (str[i] == '$')
		{
			if (i > 0)
				if (str[i - 1] == '=')
					return -1;
            return inside_quotes;
		}
        i++;
    }
    return -1;
}

char **make_tab(char *s, t_env *head, t_command **node)
{
	if (quotes_validity(s) == 1)
	{
		ft_putstr_fd("Parse Error near quote\n", 2);
		*((unsigned char *)exit_status()) = 2;
		return (NULL);
	}
	char *n;
	if (!s)
		return (NULL);
	else
		n = before_and_after(s);
	int len = count_words_2(s, ' ');
	(*node)->token = ft_malloc(sizeof(int) * (len + 1), 0);
	char **argst = ft_split_with_quotes(n, ' ', &(*node)->token);
	char **args = ft_malloc((calculate2(argst, head) + 1) * sizeof(char *), 0);
	int z = 0;
	int y = 0;
	while (argst[z])
	{
		char *expanded = expand(argst[z], head);
		if (expanded && expanded[0] == '\0')
		{
			z++;
			continue;
		}
		char **tmp = ft_split(expand(argst[z], head), ' ');
		if (ft_strcmp(argst[z], expand(argst[z], head)))
		{
			if (!strcmp(expand(argst[z], head), ""))
			{
				z++;
				continue ;
			}
			if (argst[z][0] == '$' && argst[z][1] == '"' && argst[z][2] == '"')
			{
				args[z] = ft_strdup("");
				break ;
			}
			if (z > 0)
			{
				if (!ft_strcmp(args[z - 1], ">"))
				{
					if ((ambiguous(tmp) == 1 || !tmp[0]))
					{
						ft_putstr_fd("minishell: ", 2);
						ft_putstr_fd(argst[z], 2);
						ft_putstr_fd(": ambiguous redirect\n", 2);
						args[0] = ft_strdup("true");
						*(unsigned char *)exit_status() = 1;
						return (args);
					}
				}
			}
			if (is_dollar_inside_quotes(argst[z]))
				args[y++] = ft_strdup(expand(argst[z], head));
			else if (!is_dollar_inside_quotes(argst[z]))
			{
				int x = 0;
				while (tmp[x])
					args[y++] = ft_strdup(tmp[x++]);
			}
		}
		else if (!ft_strcmp(argst[z], "<<"))
			args[y++] = ft_strdup(argst[z]);
		else
			args[y++] = ft_strdup(expand(argst[z], head));
		z++;
	}
	args[y] = NULL;
	if (check_parse(args) != -1)
	{
		int i = check_parse(args);
		if (args[i + 1])
			ft_error(args[i + 1]);
		else
			ft_error("newline");
		*((unsigned char *)exit_status()) = 2;
		return(NULL);
	}
	return (args);
}

static void ft_cmdadd_back(t_command **lst, t_command *new_env)
{
	if (lst == NULL || new_env == NULL)
		return;
	if (*lst == NULL)
	{
		*lst = new_env;
		new_env->next = NULL;
		return;
	}
	while ((*lst)->next != NULL && (*lst)->pipe == 1)
		lst = &(*lst)->next;
	(*lst)->next = new_env;
	(*lst)->pipe = 1;
}

void	remove_from_array2(t_command **new)
{
	int	i = 0;
	int j = 0;
	int size = 0;
	while ((*new)->args2[size])
		size++;
	char **args = (char **)ft_malloc(sizeof(char *) * (size + 1), 0);
	if (!args)
		return ;
	while ((*new)->args2[i])
	{
		if ((*new)->args2[i][0] == '>' && !(*new)->args2[i][1] && (*new)->token[i])
			i += 2;
		else if ((*new)->args2[i][0] == '>' && (*new)->args2[i][1] == '>' && (*new)->token[i])
			i += 2;
		else if ((*new)->args2[i][0] == '<' && (*new)->args2[i][1] == '<' && (*new)->token[i])
			i += 2;
		else if ((*new)->args2[i][0] == '<' && !(*new)->args2[i][1] && (*new)->token[i])
			i += 2;
		else
			args[j++] = ft_strdup((*new)->args2[i++]);
	}
	args[j] = NULL;
	(*new)->args2 = args;
}

t_command *create_node(char *s, t_env *head)
{
	t_command *new = (t_command *)ft_malloc(sizeof(t_command) + 1, 0);
	if (!new)
		return (NULL);
	new->args = ft_strdup(s);
	if (!s)
		return (NULL);
	new->args2 = make_tab(s, head, &new);
	if (!new->args2)
		return (NULL);
	int i = 0;
	new->redirect = 0;
	new->append = 0;
	new->dredirect = 0;
	new->dappend = 0;
	new->pipe = 0;
	new->exit_status = 0;
	int fd = 0;
	while (new->args2[i])
	{
		if (new->args2[i][0] == '>' && !new->args2[i][1] && new->token[i])
		{
			fd = open_with_gc(new->args2[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644, 1);
			if (fd < 0)
			{
				if (errno == 21)
					error_exit(&new->args2[i + 1], ": Is a directory\n", 1);
				else if (errno == 13)
					error_exit(&new->args2[i + 1], ": Permission denied\n", 1);
				else if (errno == 2)
					error_exit(&new->args2[i + 1], ": No such file or directory\n", 1);
				new->args2[0] = ft_strdup("true");
				new->exit_status = 1;
				return (new);
			}
			new->fd_out = fd;
			new->redirect++;
		}
		else if (new->args2[i][0] == '>' && new->args2[i][1] == '>' && new->token[i])
		{
			fd = open_with_gc(new->args2[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0644, 1);
			if (fd < 0)
			{
				if (errno == 21)
					error_exit(&new->args2[i + 1], ": Is a directory\n", 1);
				else if (errno == 13)
					error_exit(&new->args2[i + 1], ": Permission denied\n", 1);
				else if (errno == 2)
					error_exit(&new->args2[i + 1], ": No such file or directory\n", 1);
				new->args2[0] = ft_strdup("true");
				new->exit_status = 1;
				return (new);
			}
			new->fd_out = fd;
			new->dredirect++;
		}
		else if (new->args2[i][0] == '<' && !new->args2[i][1] && new->token[i])
		{
			fd = open_with_gc(new->args2[i + 1], O_RDONLY, 0, 0);
			if (fd < 0)
			{
				if (errno == 21)
					error_exit(&new->args2[i + 1], ": Is a directory\n", 1);
				else if (errno == 13)
					error_exit(&new->args2[i + 1], ": Permission denied\n", 1);
				else if (errno == 2)
					error_exit(&new->args2[i + 1], ": No such file or directory\n", 1);
				new->args2[0] = ft_strdup("true");
				new->exit_status = 1;
				return (new);
			}
			new->fd_in = fd;
			new->append++;
		}
		else if (new->args2[i][0] == '<' && new->args2[i][1] == '<' && new->token[i])
		{
			fd = open_with_gc("/tmp/auto", O_CREAT | O_RDWR | O_TRUNC, 0644, 0);
			if (fd < 0)
			{
				if (errno == 21)
					error_exit(&new->args2[i + 1], ": Is a directory\n", 1);
				else if (errno == 13)
					error_exit(&new->args2[i + 1], ": Permission denied\n", 1);
				else if (errno == 2)
					error_exit(&new->args2[i + 1], ": No such file or directory\n", 1);
				new->args2[0] = ft_strdup("true");
				*((unsigned char *)exit_status()) = 1;
				new->exit_status = 1;
				return (new);
			}
			new->fd_in = open_with_gc("/tmp/auto", O_RDONLY, 0, 0);
			if (new->fd_in < 0)
			{
				if (errno == 21)
					error_exit(&new->args2[i + 1], ": Is a directory\n", 1);
				else if (errno == 13)
					error_exit(&new->args2[i + 1], ": Permission denied\n", 1);
				else if (errno == 2)
					error_exit(&new->args2[i + 1], ": No such file or directory\n", 1);
				new->args2[0] = ft_strdup("true");
				*((unsigned char *)exit_status()) = 1;
				new->exit_status = 1;
				return (new);
			}
			unlink("/tmp/auto");
			heredocu(new->args2[i + 1], &fd, head, new->token[i + 1]);
			rl_catch_signals = 0;
			if (g_signal == 1)
			{
				dup2(fd, 0);
				g_signal = 0;
				setup_signals();
				*((unsigned char *)exit_status()) = 1;
				new->exit_status = 1;
				ft_fds();
				return (NULL);
			}
			if (ft_strcmp(new->args2[0], "<<") == 0)
				new->args2[0] = ft_strdup("true");
			new->dappend++;
		}
		i++;
	}
	new->next = NULL;
	remove_from_array2(&new);
	return (new);
}

int check_pipe(char *line)
{
    int i = 0;
    int pipe_count = 0;
    int command_started = 0;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] == '|')
        return (1);

    while (line[i])
    {
		if (line[i] == '\'' || line[i] == '"')
		{
			char c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;	
		}
        if (line[i] == '|')
        {
            pipe_count++;
            if (pipe_count > 1 || !command_started)
                return (1);
            command_started = 0;
        }
        else if (line[i] != ' ' && line[i] != '\t')
        {
            pipe_count = 0;
            command_started = 1;
        }
		if (line[i])
       		i++;
    }
    while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'))
        i--;
    if (i > 0 && line[i - 1] == '|')
        return (1);
    return (0); 
}

t_command *parsing(char *line, t_env *head)
{
	t_command *stack_of_cmd = NULL;
	if (check_pipe(line))
	{
		ft_putstr_fd(" syntax error near unexpected token `|'\n", 2);
		*((unsigned char *)exit_status()) = 2;
		return (NULL);
	}
	char *s = ft_strtok(line, '|');
	while (s)
	{
		t_command *new = create_node(s, head);
		if (!new)
			return (NULL);
		ft_cmdadd_back(&stack_of_cmd, new);
		s = ft_strtok(NULL, '|');

	}
	return (stack_of_cmd);
}
