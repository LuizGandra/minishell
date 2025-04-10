/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:06:14 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/10 15:34:06 by lhenriqu         ###   ########.fr       */
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
	t_prop	*props;
	char	*str;

	i = 0;
	props = &node->props;
	node->full_content = ft_strdup("");
	while (i < props->size)
	{
		str = props->content[i].str;
		node->full_content = ft_strjoin_with_free(node->full_content, str);
		i++;
	}
	ft_gc_add(node->full_content);
}

void	assign_redirects(t_token_list *list)
{
	t_token_list	*redirect;
	t_token_list	*file;

	while (list)
	{
		if (is_redirector(list->token))
		{
			redirect = list;
			file = redirect->next;
			redirect->token.file = &file->token;
			redirect->next = file->next;
			if (file->next)
				file->next->prev = redirect;
			file->next = NULL;
			file->prev = NULL;
		}
		list = list->next;
	}
}
