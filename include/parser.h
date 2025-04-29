/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:59:41 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 15:58:41 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexing.h"
# include "minishell.h"

typedef struct s_token_list	t_token_list;
typedef enum e_token_type	t_token_type;

typedef enum e_tree_type
{
	TREE_AND,
	TREE_PIPE,
	TREE_OR,
	TREE_REDIR_IN,
	TREE_REDIR_OUT,
	TREE_REDIR_OUT_APP,
	TREE_REDIR_HDOC,
	TREE_CMD,
	TREE_SUBSHELL
}						t_tree_type;

// enum for listing the priority order of token types
typedef enum e_token_priority
{
	TOK_WORD_PRIORITY,
	TOK_BRACKET_PRIORITY,
	TOK_REDIR_PRIORITY,
	TOK_PIPE_PRIORITY,
	TOK_AND_OR_PRIORITY
}						t_token_priority;

// enum for listing the types of tree nodes
typedef enum e_tree_hierarchy
{
	ROOT,
	LEFT_CHILD,
	RIGHT_CHILD
}						t_tree_hierarchy;

typedef struct s_exec_tree
{
	t_tree_type			type;
	t_token_list		*command;
	t_token_list		*file;
	int					here_doc_fd;
	struct s_exec_tree	*subshell;
	struct s_exec_tree	*left;
	struct s_exec_tree	*right;
}						t_exec_tree;

// ================================= HERE DOC =================================
int						here_doc(char *delimiter);

// ================================ TOKEN UTILS ===============================
t_token_list			*ft_lstlast(t_token_list *lst);
t_token_list			*ft_sublist(t_token_list *lst, t_token_list *start,
							t_token_list *end);

// =================================== UTILS ==================================
t_token_priority		get_priority_by_type(t_token_type type);
int						compare_priority(t_token_type type_1,
							t_token_type type_2);
t_token_list			*get_next_token(t_token_list *token_list,
							t_tree_hierarchy hierarchy);
t_bool					is_subshell(t_token_list *token_list);
void					pass_brackets(t_token_list **token_list,
							t_tree_hierarchy hierarchy);

// TODO REMOVE
void					print_token_list(t_token_list *list);

#endif