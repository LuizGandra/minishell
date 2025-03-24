/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:51:27 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/24 12:49:16 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static void	read_new_line(t_token *node, char qoute)
{
	char	*tmp;
	char	*line;

	tmp = strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			node->error = TRUE;
			return ;
		}
		if (!ft_strchr(line, qoute))
		{
			tmp = ft_strjoin_with_free(tmp, line);
			tmp = ft_strjoin_with_free(tmp, "\n");
		}
		else
		{
			line = ft_substr(line, 0, ft_strchr(line, qoute) - line);
			tmp = ft_strjoin_with_free(tmp, line);
			return ;
		}
	}
}

static char	*handle_quote(t_token *node, char *input)
{
	int		len;
	char	quote;

	if (*input != '\'' && *input != '"')
		return (input);
	quote = *input;
	len = 1;
	while (input[len - 1] && input[len - 1] != quote)
		len++;
	node->content[node->size].str = ft_substr(input, 0, len);
	node->content[node->size].quote = quote;
	if (quote == '\'')
		node->content[node->size].expandible = FALSE;
	else
		node->content[node->size].expandible = TRUE;
	node->size++;
	if (!input[len - 1])
		read_new_line(node, quote);
	ft_gc_add(node->content[node->size].str);
	return (input + len);
}

static char	*handle_word(t_token *node, char *input)
{
	size_t	len;

	input = handle_quote(node, input);
	if (node->error)
		return (input + ft_strlen(input));
	while (*input && is_word(*input))
	{
		len = 0;
		while (is_word(input[len]))
			len++;
		node->content[node->size].str = ft_substr(input, 0, len);
		node->content[node->size].expandible = TRUE;
		node->size++;
		input += len;
		ft_gc_add(node->content[node->size].str);
		input = handle_quote(node, input);
		if (node->error)
			return (input + ft_strlen(input));
	}
	fill_full_content(node);
	node->type = WORD;
	return (input);
}

static char	*fill_token(t_token *node, char *input)
{
	t_state	state;

	input = left_trim(input);
	state = get_initial_state(*input);
	if ((state >= F_OR && state <= F_CLOSE_BRACKET) || state == S_ERROR)
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
	input = handle_word(node, input);
	if (node->error)
	{
		ft_printf_fd(2,
			"minishell: unexpected EOF while looking for matching `''\n");
		ft_printf_fd(2, EOF_ERROR);
	}
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
	if (node->token.error)
		return (NULL);
	init = validate_tokens(init);
	return (init);
}
