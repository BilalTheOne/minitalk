/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaida <ohaida@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:24:15 by ohaida            #+#    #+#             */
/*   Updated: 2023/11/06 15:56:57 by ohaida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char const *s)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 1;
	while (*s)
	{
		if (*s == ' ' || (*s >= 9 && *s <= 13))
			in_word = 1;
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

static char	*ft_strdub(char const *s, int len)
{
	char	*result;
	int		i;

	result = (char *)ft_malloc((len + 1), 0);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static void	fill(char **result, char const *s,int word_count)
{
    int	i;
    int	len;

    i = 0;
    while (i < word_count)
    {
        while (*s == ' ' || (*s >= 9 && *s <= 13))
            s++;
        len = 0;
        while (s[len] && !(s[len] == ' ' || (s[len] >= 9 && s[len] <= 13)))
            len++;
        result[i] = ft_strdub(s, len);
        s += len;
        i++;
    }
}

char	**ft_split_input(char const *s)
{
	int		word_count;
	char	**result;

	if (!s)
		return (NULL);
	word_count = count_words(s) + 1;
	result = (char **)ft_malloc(sizeof(char *) * (word_count + 1), 0);
	if (!result)
		return (NULL);
	fill(result, s, word_count);
	result[word_count] = NULL;
	return (result);
}
