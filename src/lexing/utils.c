/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:06:14 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/19 09:03:20 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static t_bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

t_bool	is_word(char c)
{
	return (c != '&' && c != '|' && c != '\'' && c != '"' && c != '<'
		&& c != '>' && c != '(' && c != ')' && c != ';' && c != ' '
		&& c != '\0' && !ft_isspace(c));
}

char	*left_trim(char *input)
{
	while (*input && ft_isspace(*input))
		input++;
	return (input);
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
	else if (c == ';')
		return (F_SEMICOLON);
	else if (is_word(c))
		return (S_WORD);
	return (S_ERROR);
}
