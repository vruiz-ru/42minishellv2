/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:58:07 by aghergut          #+#    #+#             */
/*   Updated: 2025/07/23 15:04:03 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "strings.h"

static void	free_memory(char **s, int pos)
{
	while (pos > 0)
		free(s[--pos]);
	free(s);
}

static int	count_arrays(char *str, char c)
{
	int	word;

	word = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			word++;
		while (*str != c && *str)
			str++;
	}
	return (word);
}

static char	**assign(char **sp, int pos, char *s, char c)
{
	size_t	s_len;
	size_t	sub_len;
	size_t	start;

	start = 0;
	s_len = ft_strlen(s);
	while (start < s_len)
	{
		sub_len = 0;
		while (s[start] != c && s[start] != 0)
		{
			sub_len++;
			start++;
		}
		if ((s[start] == c && sub_len > 0) || start == s_len)
		{
			sp[pos] = ft_substr(s, start - sub_len, sub_len);
			if (sp[pos] == 0)
				return (free_memory(sp, pos), NULL);
			pos++;
		}
		start++;
	}
	return (sp);
}

char	**ft_split(char *str, char c)
{
	char	**splits;
	int		words;

	if (str == NULL)
		return (NULL);
	words = count_arrays(str, c);
	splits = (char **) ft_calloc(words + 1, sizeof(char *));
	if (!splits)
		return (0);
	if (!*str)
		return (splits);
	return (assign(splits, 0, str, c));
}
