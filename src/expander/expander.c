/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:47:20 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/25 15:26:43 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	expand_word(t_token *token)
{
	size_t			i;
	char			*str;
	t_content_part	*part;

	while (i < token->size)
	{
		part = &token->content[i];
		if (part->quote != '\'')
			expand_vars(part);
		if (part->quote == '\0')
		{
			str = part->str;
			while (*str)
			{
				if (*str == '*')
					*str = '\x11';
			}
		}
		i++;
	}
	ft_gc_free(token->full_content);
	fill_full_content(token);
	expand_wildcards(token);
}

void	expand(t_token_list *token_list)
{
	t_token_list	*current;
	t_token			*token;

	current = token_list;
	while (current)
	{
		token = &current->token;
		if (token->type == WORD)
			expand_word(token);
		current = current->next;
	}
}
