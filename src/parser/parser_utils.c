/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 09:52:05 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/17 10:03:23 by lcosta-g         ###   ########.fr       */
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
	ft_printf("get next token foi chamada com hierarchy %i e com o token (%s, %i)\n",
			hierarchy, token_list->token.full_content, token_list->token.type);
	if (hierarchy == ROOT || hierarchy == LEFT_CHILD)
	{
		if (token_list->prev)
			ft_printf("retornou o proximo token: %i\n", token_list->prev->token.type);
		return (token_list->prev);
	}
	else
	{
		if (token_list->next)
			ft_printf("retornou o token anterior: %i\n", token_list->next->token.type);
		return (token_list->next);
	}
}

t_bool	is_a_subshell(t_token_list *token_list)
{
	if (token_list->token.type == TOK_OPEN_BRACKET
		&& ft_lstlast(token_list)->token.type == TOK_CLOSE_BRACKET)
		return (TRUE);
	return (FALSE);
}

void	pass_brackets(t_token_list **token_list, t_tree_hierarchy hierarchy)
{
	while (*token_list)
	{
		if ((*token_list)->prev
			&& ((*token_list)->prev->token.type == TOK_OPEN_BRACKET
				|| (*token_list)->prev->token.type == TOK_CLOSE_BRACKET))
			break ;
		*token_list = get_next_token(*token_list, hierarchy);
	}
}
