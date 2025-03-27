/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:06:14 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/25 13:04:00 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

t_bool	is_word(char c)
{
	return (c != '&' && c != '|' && c != '\'' && c != '"' && c != '<'
		&& c != '>' && c != '(' && c != ')' && c != '\0' && !ft_isspace(c));
}

char	*left_trim(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	return (input);
}

void	fill_full_content(t_token *node)
{
	size_t	i;
	char	*str;

	i = 0;
	node->full_content = ft_strdup("");
	while (i < node->size)
	{
		str = node->content[i].str;
		node->full_content = ft_strjoin_with_free(node->full_content, str);
		i++;
	}
	ft_gc_add(node->full_content);
}
