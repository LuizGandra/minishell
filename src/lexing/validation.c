/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:48 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/20 15:07:20 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_bool	check_brackets(t_token_list *list)
{
	int				open_brackets;
	t_token_list	*current;

	open_brackets = 0;
	current = list;
	while (current)
	{
		if (current->token.type == OPEN_BRACKET)
			open_brackets++;
		if (current->token.type == CLOSE_BRACKET)
			open_brackets--;
		current = current->next;
	}
	if (open_brackets < 0)
	{
		ft_printf_fd(2, SYNTAX_ERROR, ")");
		return (FALSE);
	}
	if (open_brackets > 0)
	{
		ft_printf_fd(2, SYNTAX_ERROR, "(");
		return (FALSE);
	}
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
	{
		ft_printf_fd(2, SYNTAX_ERROR, current->token.content);
		return (FALSE);
	}
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
		if (is_redirector(current->token) && current->next->token.type != WORD)
			return (print_token_error(current->next));
		if (!validate_separators(current))
			return (NULL);
		if (!validate_brackets(current))
			return (NULL);
		current = current->next;
	}
	if (!check_brackets(tokens))
		return (NULL);
	return (tokens);
}
