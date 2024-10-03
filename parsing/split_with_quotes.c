/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:19:53 by bel-barb          #+#    #+#             */
/*   Updated: 2024/08/28 10:24:30 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_2(char const *s, char c)
{
    int	count;
    int	in_word;
    int	inside_quote;

    count = 0;
    in_word = 1;
    inside_quote = 0;
    while (*s)
    {
        if (*s == c && !inside_quote)
            in_word = 1;
        else if ((*s == '"' || *s == '\'') && !inside_quote)
            inside_quote = *s;
        else if ((*s == '"' || *s == '\'') && inside_quote == *s)
        {
            if (s > s + 1 && *(s - 1) == inside_quote && (*(s + 1) == c || *(s + 1) == '\0' || *(s - 2) == c))
                count++;
            inside_quote = 0;
        }
        else
        {
            if (in_word)
            {
                in_word = 0;
                count++; 
            }
        }
        s++;
    }
    return (count);
}

static char	*ft_strdub2(char const *s, int len)
{
    char	*result;
    int		i;
    int		j;

    result = (char *)ft_malloc(len + 1, 0);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (i < len)
    {
        result[j++] = s[i++];
    }
    result[j] = '\0';
    return (result);
}


static void	fill(char **result, char const *s, char c, int word_count, int *token)
{
    int	i;
    int	len;
    int	inside_quote;
    int	is_quote;

    i = 0;
    inside_quote = 0;
    while (i < word_count)
    {
        while (*s == c)
            s++;
        len = 0;
        inside_quote = 0;
        is_quote = 0;
        while (s[len] && (s[len] != c || inside_quote))
        {
            if ((s[len] == '"' || s[len] == '\'')) 
            {
                if (!inside_quote)
                    inside_quote = s[len];
                else if (inside_quote == s[len])
                    inside_quote = 0;
                is_quote = 1;
            }
            len++;
        }
        if ((s[0] == '"' && s[1] == '"' && (s[2] == c || s[2] == '\0')) ||
            (s[0] == '\'' && s[1] == '\'' && (s[2] == c || s[2] == '\0')))
        {
            result[i] = ft_strdup("");
            token[i] = 1;
            s += 2;
        }
        else if (len > 0)
        {
            result[i] = ft_strdub2(s, len);
            if (!is_quote)
                token[i] = 1;
            if (is_quote)
                token[i] = 0;
            s += len;
        }
        i++;
    }
    result[i] = NULL;
}

char	**ft_split_with_quotes(char const *s, char c, int **token)
{
    int		word_count;
    char	**result;

    if (!s)
        return (NULL);
    word_count = count_words_2(s, c);
    result = ft_malloc(sizeof(char *) * (word_count + 1), 0);
    if (!result)
        return (NULL);
    *token = ft_malloc((word_count + 1) * sizeof(int), 0);
    fill(result, s, c, word_count, *token);
    return (result);
}
