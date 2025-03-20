/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:40:26 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/20 14:49:25 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

# define SYNTAX_ERROR "minishell: syntax error near unexpected token `%s'\n"

typedef enum e_state
{
	S_ERROR = -1,
	S_START,
	S_PIPE,
	S_AND,
	S_REDIR_IN,
	S_REDIR_OUT,
	S_WORD,
	S_SINGLE_QOUTE,
	S_QOUTE,
	F_OR,
	F_AND,
	F_REDIR_HDOC,
	F_REDIR_OUT_APP,
	F_WORD,
	F_PIPE,
	F_REDIR_IN,
	F_REDIR_OUT,
	F_OPEN_BRACKET,
	F_CLOSE_BRACKET,
	F_SEMICOLON,
}						t_state;

typedef enum e_token_type
{
	INVALID,
	OR = 8,
	AND,
	REDIR_HDOC,
	REDIR_OUT_APP,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	OPEN_BRACKET,
	CLOSE_BRACKET,
	SEMICOLON,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*content;
	size_t				content_size;
}						t_token;

typedef struct s_token_list
{
	t_token				token;
	struct s_token_list	*next;
}						t_token_list;

t_token_list			*get_token_list(char *input);
t_bool					is_word(char c);
char					*left_trim(char *input);
t_state					get_seccond_state(char *input, t_state state);
t_state					get_initial_state(char c);
t_token_list			*validate_tokens(t_token_list *tokens);
t_bool					is_separator(t_token token);
t_bool					is_semicolon(t_token c);
t_bool					is_redirector(t_token token);
t_bool					can_finish(t_token c);
void					*print_token_error(t_token_list *node);

#endif