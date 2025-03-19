/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:21:48 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/19 15:23:25 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_bool	is_redirector(t_token c)
{
	return (c.type == REDIR_IN || c.type == REDIR_OUT || c.type == REDIR_OUT_APP
		|| c.type == REDIR_HDOC);
}

static t_bool	is_separator(t_token c)
{
	return (c.type == AND || c.type == OR || c.type == PIPE);
}

static void	*print_token_error(t_token token)
{
	if (token.type == AND)
		ft_printf_fd(2, "syntax error near unexpected token `&&'\n");
	else if (token.type == OR)
		ft_printf_fd(2, "syntax error near unexpected token `||'\n");
	else if (token.type == PIPE)
		ft_printf_fd(2, "syntax error near unexpected token `|'\n");
	else if (token.type == SEMICOLON)
		ft_printf_fd(2, "syntax error near unexpected token `;'\n");
	else if (token.type == REDIR_IN)
		ft_printf_fd(2, "syntax error near unexpected token `<'\n");
	else if (token.type == REDIR_OUT)
		ft_printf_fd(2, "syntax error near unexpected token `>'\n");
	else if (token.type == REDIR_OUT_APP)
		ft_printf_fd(2, "syntax error near unexpected token `>>'\n");
	else if (token.type == REDIR_HDOC)
		ft_printf_fd(2, "syntax error near unexpected token `<<'\n");
	else if (token.type == OPEN_BRACKET)
		ft_printf_fd(2, "syntax error near unexpected token `('\n");
	else if (token.type == CLOSE_BRACKET)
		ft_printf_fd(2, "syntax error near unexpected token `)'\n");
	else if (token.type == INVALID)
		ft_printf_fd(2, "syntax error near unexpected token `&'\n");
	return (NULL);
}

static t_token	last_token(t_token_list *list)
{
	while (list->next)
		list = list->next;
	return (list->token);
}

t_token_list	*validate_tokens(t_token_list *tokens)
{
	t_token_list	*current;

	current = tokens;
	if (is_separator(current->token))
		return (print_token_error(current->token));
	if (is_separator(last_token(current)))
		return (print_token_error(last_token(current)));
	while (current)
	{
		if (current->token.type == INVALID)
			return (print_token_error(current->token));
		if (is_redirector(current->token))
		{
			if (!current->next)
				ft_printf_fd(2,
					"syntax error near unexpected token `newline'\n");
			else if (current->next->token.type != WORD)
				return (print_token_error(current->next->token));
		}
		current = current->next;
	}
	return (tokens);
}
