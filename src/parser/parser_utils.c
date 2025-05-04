/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:52:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 00:32:13 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_priority	get_priority_by_type(t_token_type type)
{
	if (type == TOK_WORD)
		return (TOK_WORD_PRIORITY);
	else if (type == TOK_OPEN_BRACKET || type == TOK_CLOSE_BRACKET)
		return (TOK_BRACKET_PRIORITY);
	else if (type == TOK_REDIR_IN || type == TOK_REDIR_OUT
		|| type == TOK_REDIR_OUT_APP || type == TOK_REDIR_HDOC)
		return (TOK_REDIR_PRIORITY);
	else if (type == TOK_PIPE)
		return (TOK_PIPE_PRIORITY);
	else if (type == TOK_OR || type == TOK_AND)
		return (TOK_AND_OR_PRIORITY);
	return (-1);
}

int	compare_priority(t_token_type type_1, t_token_type type_2)
{
	t_token_priority	priority_1;
	t_token_priority	priority_2;

	priority_1 = get_priority_by_type(type_1);
	priority_2 = get_priority_by_type(type_2);
	if (priority_1 > priority_2)
		return (1);
	else if (priority_1 < priority_2)
		return (-1);
	else
		return (0);
}

t_token_list	*get_next_token(t_token_list *token_list,
		t_tree_hierarchy hierarchy)
{
	if (hierarchy == ROOT || hierarchy == LEFT_CHILD)
		return (token_list->prev);
	else
		return (token_list->next);
}

void	pass_brackets(t_token_list **token_list, t_tree_hierarchy hierarchy)
{
	int				brackets_count;
	t_token_type	open_bracket;
	t_token_type	close_bracket;

	brackets_count = 0;
	if ((*token_list)->token.type == TOK_OPEN_BRACKET)
	{
		open_bracket = TOK_OPEN_BRACKET;
		close_bracket = TOK_CLOSE_BRACKET;
	}
	else
	{
		open_bracket = TOK_CLOSE_BRACKET;
		close_bracket = TOK_OPEN_BRACKET;
	}
	while (*token_list)
	{
		if ((*token_list)->token.type == open_bracket)
			brackets_count++;
		else if ((*token_list)->token.type == close_bracket)
			brackets_count--;
		else if (brackets_count == 0)
			break ;
		*token_list = get_next_token(*token_list, hierarchy);
	}
}

t_bool	is_subshell(t_token_list *token_list)
{
	pass_brackets(&token_list, RIGHT_CHILD);
	if (!token_list)
		return (TRUE);
	return (FALSE);
}
