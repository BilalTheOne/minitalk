/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:21:38 by bel-barb          #+#    #+#             */
/*   Updated: 2024/08/28 10:54:37 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int calculate(char *s, t_env *head)
{
	int i = 0;
	int c = 0;
	int inside_single = 0;
	int inside_double = 0;
	char *x = ft_strdup(s);

	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (!inside_double)
			{
				inside_single = !inside_single;
				i++;
			}
			else
			{
				c++;
				i++;
			}
		}
		else if (s[i] == '"')
		{
			if (!inside_single)
			{
				inside_double = !inside_double;
				i++;
			}
			else
			{
				c++;
				i++;
			}
		}
		else if (s[i] == '$' && !inside_single)
		{
			if (inside_double && (s[i + 1] == '"' || s[i + 1] == '\''))
            {
                c++;
				i++;
                continue;
            }

			if (s[i + 1] == '"' || s[i + 1] == '\'')
			{
				i++;
				continue;
			}

			if (s[i + 1] == '?')
			{
				char *env = get_env_value(head, "?");
				if (env)
				{
					while (*env)
					{
						c++;
						env++;
					}
				}
				i += 2;
				continue;
			}

			if (ft_isdigit(s[i + 1]))
			{
				i += 2;
				continue;
			}

			if (!ft_isalpha(s[i + 1]) && s[i + 1] != '_')
			{
				c++;
				i++;
				continue;
			}

			i++;
			char *tmp = ft_strttok(x + i, " \'\"");
			char *env = get_env_value(head, tmp);
			if (env)
			{
				while (*env)
				{
					c++;
					env++;
				}
			}
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"' && ft_isalnum(s[i]))
				i++;
		}
		else
		{
			c++;
			i++;
		}
	}

	return (c);
}


char *expand(char *s, t_env *head)
{
	int i = 0;
	int j = 0;
	int inside_single = 0;
	int inside_double = 0;
	int c = calculate(s, head);
	char *expanded = ft_malloc(c + 1, 0);
	if (!expanded)
		return (NULL);
	char *x = ft_strdup(s);
	while (s[i])
	{
		if (s[i] == '\'')
		{
			if (!inside_double)
			{
					inside_single = !inside_single;
					i++;
			}
			else
				expanded[j++] = s[i++];
		}
		else if (s[i] == '"')
		{
			if (!inside_single)
			{
					inside_double = !inside_double;
					i++;
			}
			else
				expanded[j++] = s[i++];
		}
		else if (s[i] == '$' && !inside_single)
		{
			if (inside_double && (s[i + 1] == '"' || s[i + 1] == '\''))
            {
                expanded[j++] = s[i++];
                continue;
            }
			if (s[i + 1] == '"' || s[i + 1] == '\'')
			{
				i++;
				continue;
			}
			if (s[i + 1] == '?')
			{
				char *env = get_env_value(head, "?");
				if (env)
				{
					while (*env)
						expanded[j++] = *env++;
				}
				i += 2;
				continue ;
			}
			if (ft_isdigit(s[i + 1]))
			{
				i += 2;
				continue ;
			}
			if (!ft_isalpha(s[i + 1]) && s[i + 1] != '_')
			{
				expanded[j++] = s[i++];
				continue ;
			}
			i++;
			char *tmp = ft_strttok(x + i, " \'\"");
			char *env = get_env_value(head, tmp);
			if (env)
			{
				while (*env)
					expanded[j++] = *env++;
			}
			if (!env)
			{
				while (*tmp)
					s[i++] = *tmp++;
			}
			while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '"' && ft_isalnum(s[i]))
				i++;
		}
		else
			expanded[j++] = s[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}

char *before_and_after(char *s)
{
	int i = 0;
	int len = 0;
	int j = 0;
	char inside_quote = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && !inside_quote)
			inside_quote = s[i];
		else if (inside_quote && s[i] == inside_quote)
			inside_quote = 0;
		if (!inside_quote && (s[i] == '>' || s[i] == '<'))
		{
			if (s[i + 1] == '>' || s[i + 1] == '<')
				i++;
			len = len + 4;
		}
		else
			len++;
		i++;
	}
	char *new = (char *)ft_malloc(sizeof(char) * len + 1, 0);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && !inside_quote)
			inside_quote = s[i];
		else if (inside_quote && s[i] == inside_quote)
			inside_quote = 0;
		if (!inside_quote && s[i] == '>')
		{
			new[j] = ' ';
			new[j + 1] = s[i];
			if (s[i + 1] == '>')
			{
				new[j + 2] = s[i + 1];
				j++;
				i++;
			}
			new[j + 2] = ' ';
			j = j + 3;
		}
		else if (!inside_quote && s[i] == '<')
		{
			new[j] = ' ';
			new[j + 1] = s[i];
			if (s[i + 1] == '<')
			{
				new[j + 2] = s[i + 1];
				j++;
				i++;
			}
			new[j + 2] = ' ';
			j = j + 3;
		}
		else
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}
