/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:51:27 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 09:56:23 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static char	*handle_quote(t_token *node, char *input)
{
	size_t	len;
	char	quote;

	if (*input != '\'' && *input != '"')
		return (input);
	quote = *input;
	len = 0;
	while (input[len + 1] && input[len + 1] != quote)
		len++;
	node->content[node->size].str = ft_substr(input, 1, len);
	ft_gc_add(node->content[node->size].str);
	node->content[node->size].quote = quote;
	node->size++;
	if (!input[len + 1])
	{
		node->error = TRUE;
		return (input + ft_strlen(input));
	}
	return (input + len + 2);
}

static char	*handle_word(t_token *node, char *input)
{
	size_t	len;

	input = handle_quote(node, input);
	while (*input && is_word(*input))
	{
		len = 0;
		while (is_word(input[len]))
			len++;
		node->content[node->size].str = ft_substr(input, 0, len);
		ft_gc_add(node->content[node->size].str);
		node->size++;
		input += len;
		input = handle_quote(node, input);
	}
	if (!node->error)
		fill_full_content(node);
	node->type = TOK_WORD;
	return (input);
}

static char	*fill_token(t_token *node, char *input)
{
	t_state	state;

	input = left_trim(input);
	state = get_initial_state(*input);
	if (state >= F_OR && state <= F_CLOSE_BRACKET)
	{
		node->type = (t_token_type)state;
		return (input + 1);
	}
	state = get_seccond_state(input, state);
	if (state >= F_OR && state <= F_CLOSE_BRACKET)
	{
		node->type = (t_token_type)state;
		if (state >= F_OR && state <= F_REDIR_OUT_APP)
			return (input + 2);
		return (input + 1);
	}
	if (state == S_ERROR)
		return (input + 1);
	input = handle_word(node, input);
	if (node->error)
		ft_printf_fd(2, QUOTE_ERROR, node->content[node->size - 1].quote);
	return (input);
}

t_token_list	*get_token_list(char *input)
{
	t_token_list	*node;
	t_token_list	*init;
	t_token_list	*prev;

	if (!input)
		return (NULL);
	init = NULL;
	while (*input)
	{
		node = ft_gc_malloc(sizeof(t_token_list));
		if (!init)
			init = node;
		else
		{
			prev->next = node;
			node->prev = prev;
		}
		input = fill_token(&node->token, input);
		prev = node;
	}
	if (node->token.error)
		return (NULL);
	init = validate_tokens(init);
	expand(&init);
	return (init);
}
