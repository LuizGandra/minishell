/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:47:20 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 16:48:50 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_token_list	*expand_word(t_token *token, t_token_list **list)
{
	size_t			i;
	char			*str;
	t_content_part	*part;

	i = 0;
	while (i < token->props.size)
	{
		part = &token->props.content[i];
		if (part->quote != '\'')
			expand_vars(part);
		if (part->quote == '\0')
		{
			str = part->str;
			while (*str)
			{
				if (*str == '*')
					*str = '\x11';
				str++;
			}
		}
		i++;
	}
	ft_gc_free(token->full_content);
	fill_full_content(token);
	return (expand_wildcards(token, list));
}

static void	finish_wildcard(t_token *token)
{
	char	*str;

	str = token->full_content;
	while (*str)
	{
		if (*str == '\x11')
			*str = '*';
		str++;
	}
}

void	expand(t_token_list **token_list, t_bool file)
{
/*	t_token_list	*current;
	t_token			*token;

	current = *token_list;
	while (current)
	{
		if (file)
			token = current->token.file;
		else
			token = &current->token;
		if (token->type == TOK_WORD)
		{
			current = expand_word(token, token_list);
			finish_wildcard(token);
		}
		current = current->next;
	}
*/
	}
