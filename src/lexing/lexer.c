/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:51:27 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/17 19:15:35 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static void read_new_line(t_token *node, char qoute)
{
	char *line;
	char *tmp;
	size_t len;

	line = readline(C_BLD "quote>" C_RST);
	if (!line)
		return;
	len = 0;
	while (line[len] && line[len] != qoute)
	{
		if (line[len] != qoute)
			len++;
	}
	tmp = ft_substr(line, 0, len);
	node->content = ft_strjoin_with_free(node->content, tmp);
	if (!line[len])
		read_new_line(node, qoute);
	free(line);
}

static char *handle_qoute(t_token *node, char *input, char qoute)
{
	char *tmp;
	int	 len;

	len = 0;
	if (input[len] != qoute)
		return (input);
	input++;
	node->content_size++;
	while (input[len] && input[len] != qoute)
		len++;
	tmp = ft_substr(input, 0, len);
	node->content = ft_strjoin_with_free(node->content, tmp);
	node->content_size += (len + 1);
	if (!input[len])
	{
		read_new_line(node, qoute);
		len--;
		node->content_size--;
	}
	return (input + len + 1);
}

static t_state handle_word(t_token *node, char *input, t_state state)
{
	char *tmp;
	size_t len;

	node->content = ft_strdup("");
	if (state == S_SINGLE_QOUTE)
		input = handle_qoute(node, input, '\'');
	else if (state == S_QOUTE)
		input = handle_qoute(node, input, '"');
	while (*input && is_word(*input))
	{
		len = 0;
		while (is_word(input[len]))
			len++;
		tmp = ft_substr(input, 0, len);
		node->content = ft_strjoin_with_free(node->content, tmp);
		input += len;
		node->content_size += len;
		if (*input == '\'')
			input = handle_qoute(node, input, '\'');
		else if (*input == '"')
			input = handle_qoute(node, input, '"');
	}
	return (F_WORD);
}

static char *fill_token(t_token *node, char *input)
{
	t_state state;

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
	{
		handle_error(E_INVALID_TOKEN);
		return (input + ft_strlen(input));
	}
	state = handle_word(node, input, state);
	node->type = (t_token_type)state;
	return (input + node->content_size);
}

t_token_list *get_token_list(char *input)
{
	t_token_list *node;
	t_token_list *init;
	t_token_list *prev;

	if (!input)
		return (NULL);
	init = NULL;
	prev = NULL;
	while (*input)
	{
		node = ft_gc_malloc(sizeof(t_token_list));
		if (!node)
			handle_error(E_MALLOC_FAILED);
		if (!init)
			init = node;
		else
			prev->next = node;
		input = fill_token(&node->token, input);
		prev = node;
	}
	return (init);
}
