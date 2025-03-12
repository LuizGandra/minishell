/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:29:50 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/03 16:53:40 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, char c)
{
	size_t	count;

	count = 0;
	if (*str == '\0')
		return (count);
	if (c == '\0')
		return (1);
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
		{
			count++;
			while (*str != c && *str)
				str++;
		}
	}
	return (count);
}

static char	**fill_matrix(char **matrix, const char *str, char c)
{
	size_t	len;
	size_t	m_word;

	m_word = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		len = 0;
		while (str[len] != c && str[len])
			len++;
		if (len > 0)
		{
			matrix[m_word] = (char *)ft_calloc((len + 1), sizeof(char));
			if (matrix[m_word] == NULL)
			{
				ft_free_matrix((void **)matrix, free);
				return (NULL);
			}
			ft_strlcpy(matrix[m_word], str, len + 1);
			m_word++;
			str += len;
		}
	}
	return (matrix);
}

char	**ft_split(char const *str, char c)
{
	char	**matrix;
	int		count_words;

	while (*str == c && *str)
		str++;
	count_words = ft_count_words(str, c);
	matrix = (char **)ft_calloc((count_words + 1), sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	matrix = fill_matrix(matrix, str, c);
	if (matrix == NULL)
		return (NULL);
	matrix[count_words] = NULL;
	return (matrix);
}
