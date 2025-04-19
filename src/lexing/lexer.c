/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:51:27 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/18 21:53:26 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static char	*handle_quote(t_prop *props, char *input)
{
	size_t	len;
	char	quote;

	if (*input != '\'' && *input != '"')
		return (input);
	props->content = ft_recalloc(props->content, (props->size + 1)
			* sizeof(t_content_part), props->size * sizeof(t_content_part));
	quote = *input;
	len = 0;
	while (input[len + 1] && input[len + 1] != quote)
		len++;
	props->content[props->size].str = ft_substr(input, 1, len);
	ft_gc_add(props->content[props->size].str);
	props->content[props->size].quote = quote;
	props->size++;
	if (!input[len + 1])
	{
		props->error = TRUE;
		return (input + ft_strlen(input));
	}
	return (input + len + 2);
}

static char	*handle_word(t_token *node, char *input)
{
	size_t	len;
	t_prop	*props;

	props = &node->props;
	input = handle_quote(props, input);
	while (*input && is_word(*input))
	{
		props->content = ft_recalloc(props->content, (props->size + 1)
				* sizeof(t_content_part), props->size * sizeof(t_content_part));
		len = 0;
		while (is_word(input[len]))
			len++;
		props->content[props->size].str = ft_substr(input, 0, len);
		ft_gc_add(props->content[props->size].str);
		props->size++;
		input += len;
		input = handle_quote(props, input);
	}
	if (!props->error)
		fill_full_content(node);
	node->type = TOK_WORD;
	return (input);
}

static char	*fill_token(t_token *node, char *input)
{
	t_state	state;
	t_prop	*props;

	props = &node->props;
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
	if (props->error)
		ft_printf_fd(2, QUOTE_ERROR, props->content[props->size - 1].quote);
	return (input);
}

static void trim_right(char *input)
{
	char *end;

	end = input + ft_strlen(input) - 1;
	while (end >= input && ft_isspace(*end))
        end--;
	*(end + 1) = '\0';
}

t_token_list	*get_token_list(char *input)
{
	t_token_list	*node;
	t_token_list	*init;
	t_token_list	*prev;

	trim_right(input);
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
	if (node->token.props.error)
		return (NULL);
	init = validate_tokens(init);
	assign_redirects(init);
	return (init);
}
