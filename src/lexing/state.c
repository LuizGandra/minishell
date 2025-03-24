/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:05:26 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/24 11:06:05 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

t_state	get_initial_state(char c)
{
	if (c == '|')
		return (S_PIPE);
	else if (c == '&')
		return (S_AND);
	else if (c == '<')
		return (S_REDIR_IN);
	else if (c == '>')
		return (S_REDIR_OUT);
	else if (c == '\'')
		return (S_SINGLE_QOUTE);
	else if (c == '\"')
		return (S_QOUTE);
	else if (c == '(')
		return (F_OPEN_BRACKET);
	else if (c == ')')
		return (F_CLOSE_BRACKET);
	else if (is_word(c))
		return (S_WORD);
	return (S_ERROR);
}

t_state	get_seccond_state(char *input, t_state state)
{
	if (state == S_PIPE && *(input + 1) == '|')
		state = F_OR;
	else if (state == S_PIPE)
		state = F_PIPE;
	else if (state == S_AND && *(input + 1) == '&')
		state = F_AND;
	else if (state == S_AND)
		state = S_ERROR;
	else if (state == S_REDIR_IN && *(input + 1) == '<')
		state = F_REDIR_HDOC;
	else if (state == S_REDIR_IN)
		state = F_REDIR_IN;
	else if (state == S_REDIR_OUT && *(input + 1) == '>')
		state = F_REDIR_OUT_APP;
	else if (state == S_REDIR_OUT)
		state = F_REDIR_OUT;
	return (state);
}
