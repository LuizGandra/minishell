/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:57:42 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/02 07:48:37 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_bool	is_redirector(t_token c)
{
	return (c.type == TOK_REDIR_IN || c.type == TOK_REDIR_OUT
		|| c.type == TOK_REDIR_OUT_APP || c.type == TOK_REDIR_HDOC);
}

t_bool	is_separator(t_token c)
{
	return (c.type == TOK_AND || c.type == TOK_OR || c.type == TOK_PIPE);
}

t_bool	can_finish(t_token c)
{
	return (c.type == TOK_WORD || c.type == TOK_CLOSE_BRACKET);
}

void	*print_token_error(t_token_list *node)
{
	if (!node)
		ft_printf_fd(2, SYNTAX_ERROR, "newline");
	else if (node->token.type == TOK_AND)
		ft_printf_fd(2, SYNTAX_ERROR, "&&");
	else if (node->token.type == TOK_OR)
		ft_printf_fd(2, SYNTAX_ERROR, "||");
	else if (node->token.type == TOK_PIPE)
		ft_printf_fd(2, SYNTAX_ERROR, "|");
	else if (node->token.type == TOK_REDIR_IN)
		ft_printf_fd(2, SYNTAX_ERROR, "<");
	else if (node->token.type == TOK_REDIR_OUT)
		ft_printf_fd(2, SYNTAX_ERROR, ">");
	else if (node->token.type == TOK_REDIR_OUT_APP)
		ft_printf_fd(2, SYNTAX_ERROR, ">>");
	else if (node->token.type == TOK_REDIR_HDOC)
		ft_printf_fd(2, SYNTAX_ERROR, "<<");
	else if (node->token.type == TOK_OPEN_BRACKET)
		ft_printf_fd(2, SYNTAX_ERROR, "(");
	else if (node->token.type == TOK_CLOSE_BRACKET)
		ft_printf_fd(2, SYNTAX_ERROR, ")");
	else if (node->token.type == TOK_INVALID)
		ft_printf_fd(2, SYNTAX_ERROR, "&");
	return (NULL);
}
