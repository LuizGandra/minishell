/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:47:20 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 00:51:31 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	remove_token(t_token_list **list, t_token_list *current)
{
	if (!current->prev)
	{
		if (current->next)
			current->next->prev = NULL;
		*list = current->next;
	}
	else
	{
		current->prev->next = current->next;
		if (current->next)
			current->next->prev = current->prev;
	}
}

static t_token_list	*expand_word(t_token *token, t_token_list **list)
{
	int				i;
	t_content_part	*part;
	t_token_list	*current;

	i = -1;
	while (++i < (int)token->props.size)
	{
		part = &token->props.content[i];
		if (part->quote != '\'' && ft_strchr(part->str, '$'))
			expand_vars(part);
		if (part->quote == '\0')
			prepare_wildcard(part);
	}
	fill_full_content(token);
	if (token->full_content[0] == '\0')
	{
		current = get_current_token(*list, token);
		remove_token(list, current);
		return (current);
	}
	return (expand_wildcards(token, list));
}

void	expand(t_token_list **token_list)
{
	t_token_list	*current;
	t_token			*token;

	current = *token_list;
	while (current)
	{
		token = &current->token;
		if (token->type == TOK_WORD)
		{
			current = expand_word(token, token_list);
			finish_wildcard(token);
		}
		current = current->next;
	}
}
