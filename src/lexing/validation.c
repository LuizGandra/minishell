/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:48 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/20 13:11:07 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_bool	validate_redirectors(t_token_list *current)
{
	if (is_redirector(current->token) && current->next->token.type != WORD)
		return ((t_bool)print_token_error(current->next));
	return (TRUE);
}

static t_bool	validate_separators(t_token_list *current)
{
	if ((is_separator(current->token) || is_semicolon(current->token))
		&& (is_separator(current->next->token)
			|| is_semicolon(current->next->token)))
		return ((t_bool)print_token_error(current->next));
	return (TRUE);
}

static t_bool	print_word_error(t_token token)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		token.content);
	return (FALSE);
}

static t_bool	validate_brackets(t_token_list *current)
{
	if (current->token.type == OPEN_BRACKET
		&& (current->next->token.type == CLOSE_BRACKET
			|| is_separator(current->next->token)
			|| is_semicolon(current->next->token)))
		return ((t_bool)print_token_error(current->next));
	if (current->token.type == WORD && current->next
		&& current->next->token.type == OPEN_BRACKET)
		return ((t_bool)print_token_error(current->next));
	if (current->token.type == CLOSE_BRACKET && current->next
		&& current->next->token.type == WORD)
		return (print_word_error(current->next->token));
	return (TRUE);
}

t_token_list	*validate_tokens(t_token_list *tokens)
{
	t_token_list	*current;

	current = tokens;
	if (is_separator(current->token) || is_semicolon(current->token))
		return (print_token_error(current));
	while (current)
	{
		if (current->token.type == INVALID)
			return (print_token_error(current));
		if (!can_finish(current->token) && !current->next)
			return (print_token_error(NULL));
		if (!validate_redirectors(current))
			return (NULL);
		if (!validate_separators(current))
			return (NULL);
		if (!validate_brackets(current))
			return (NULL);
		current = current->next;
	}
	return (tokens);
}
