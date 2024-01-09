/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-barb <bel-barb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:31:18 by bel-barb          #+#    #+#             */
/*   Updated: 2023/11/09 22:53:07 by bel-barb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(char *str, char sp)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		while (str[i] == sp)
			i++;
		if (str[i] != '\0')
			result++;
		while (str[i] != '\0' && str[i] != sp)
			i++;
	}
	return (result);
}

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		free(ptr[i]);
	}
	free(ptr);
	return (0);
}

static char	*print_words(char *word, char const *s, int i, int wordlen)
{
	int	j;

	j = 0;
	while (wordlen > 0)
	{
		word[j] = s[i - wordlen];
		j++;
		wordlen--;
	}
	word[j] = '\0';
	return (word);
}

static char	**splited_words(char const *s, char c, char **s2, int words)
{
	int	i;
	int	new_word;
	int	word_len;

	i = 0;
	new_word = 0;
	word_len = 0;
	while (new_word < words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		s2[new_word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!s2[new_word])
			return (free_array(s2, new_word));
		print_words(s2[new_word], s, i, word_len);
		word_len = 0;
		new_word++;
	}
	s2[new_word] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	words_numb;

	if (!s)
		return (0);
	words_numb = count((char *)s, c);
	s2 = (char **)malloc(sizeof(char *) * (words_numb + 1));
	if (!s2)
		return (0);
	s2 = splited_words(s, c, s2, words_numb);
	return (s2);
}
