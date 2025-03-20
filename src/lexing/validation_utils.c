/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 07:57:42 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/20 12:01:45 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_bool	is_redirector(t_token c)
{
	return (c.type == REDIR_IN || c.type == REDIR_OUT || c.type == REDIR_OUT_APP
		|| c.type == REDIR_HDOC);
}

t_bool	is_separator(t_token c)
{
	return (c.type == AND || c.type == OR || c.type == PIPE);
}

t_bool	is_semicolon(t_token c)
{
	return (c.type == SEMICOLON);
}

t_bool	can_finish(t_token c)
{
	return (c.type == WORD || c.type == CLOSE_BRACKET || is_semicolon(c));
}

void	*print_token_error(t_token_list *node)
{
	if (!node)
		ft_printf_fd(2, "syntax error near unexpected token `newline'\n");
	else if (node->token.type == AND)
		ft_printf_fd(2, "syntax error near unexpected token `&&'\n");
	else if (node->token.type == OR)
		ft_printf_fd(2, "syntax error near unexpected token `||'\n");
	else if (node->token.type == PIPE)
		ft_printf_fd(2, "syntax error near unexpected token `|'\n");
	else if (node->token.type == SEMICOLON)
		ft_printf_fd(2, "syntax error near unexpected token `;'\n");
	else if (node->token.type == REDIR_IN)
		ft_printf_fd(2, "syntax error near unexpected token `<'\n");
	else if (node->token.type == REDIR_OUT)
		ft_printf_fd(2, "syntax error near unexpected token `>'\n");
	else if (node->token.type == REDIR_OUT_APP)
		ft_printf_fd(2, "syntax error near unexpected token `>>'\n");
	else if (node->token.type == REDIR_HDOC)
		ft_printf_fd(2, "syntax error near unexpected token `<<'\n");
	else if (node->token.type == OPEN_BRACKET)
		ft_printf_fd(2, "syntax error near unexpected token `('\n");
	else if (node->token.type == CLOSE_BRACKET)
		ft_printf_fd(2, "syntax error near unexpected token `)'\n");
	else if (node->token.type == INVALID)
		ft_printf_fd(2, "syntax error near unexpected token `&'\n");
	return (NULL);
}
