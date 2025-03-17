/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:51:27 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/17 14:12:37 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static void	read_new_line(t_token *node, char qoute)
{
	char	*line;
	char	*tmp;
	int		qnt;

	line = readline("quote>");
	if (!line)
		handle_error(E_MALLOC_FAILED);
	tmp = ft_strjoin_with_free(node->content, "\n");
	node->content = ft_strjoin_with_free(tmp, line);
	qnt = 0;
	while (*line)
	{
		if (*line == qoute)
			qnt++;
		line++;
	}
	if (qnt % 2 == 0)
		read_new_line(node, qoute);
}

static void	handle_qoute(t_token *node, char *input, char qoute)
{
	node->content_size++;
	while (input[node->content_size] && input[node->content_size] != qoute)
		node->content_size++;
	node->content = ft_substr(input, 1, node->content_size - 1);
	if (!input[node->content_size])
		read_new_line(node, qoute);
	ft_gc_add(node->content);
	node->content_size++;
}

static void	handle_word(t_token *node, char *input, t_state state)
{
	if (state == S_QOUTE)
		return (handle_qoute(node, input, '"'));
	if (state == S_SINGLE_QOUTE)
		return (handle_qoute(node, input, '\''));
	while (is_word(input[node->content_size]))
		node->content_size++;
	node->content = ft_substr(input, 0, node->content_size);
	ft_gc_add(node->content);
}

static char	*fill_token(t_token *node, char *input)
{
	t_state	state;

	input = left_trim(input);
	state = get_initial_state(*input);
	if (state >= F_OR && state <= F_SEMICOLON)
	{
		node->type = (t_token_type)state;
		return (input + 1);
	}
	state = get_seccond_state(input, state);
	if (state >= F_OR && state <= F_SEMICOLON)
	{
		node->type = (t_token_type)state;
		if (state >= F_OR && state <= F_REDIR_OUT_APP)
			return (input + 2);
		return (input + 1);
	}
	if (state == S_ERROR)
		handle_error(E_INVALID_TOKEN);
	handle_word(node, input, state);
	return (input + node->content_size);
}

t_token_list	*get_token_list(char *input)
{
	t_token_list *node;
	t_token_list *init;

	if (!input)
		return (NULL);
	init = NULL;
	while (*input)
	{
		node = ft_gc_malloc(sizeof(t_token_list));
		if (!node)
			handle_error(E_MALLOC_FAILED);
		if (!init)
			init = node;
		input = fill_token(&node->token, input);
		node = node->next;
	}
	return (init);
}