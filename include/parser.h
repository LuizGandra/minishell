/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:59:41 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/03 14:25:59 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexing.h"
# include "minishell.h"

typedef enum e_tree_type
{
	TREE_PIPE,
	TREE_AND,
	TREE_OR,
	TREE_REDIR_IN,
	TREE_REDIR_OUT,
	TREE_REDIR_APPEND,
	TREE_REDIR_HEREDOC,
	TREE_COMMAND,
	TREE_SUBSHELL
}						t_tree_type;

typedef struct s_exec_tree
{
	t_tree_type			type;
	t_token_list		*command;
	char				*file;
	int					here_doc_fd;
	struct s_exec_tree	*subshell;
	struct s_exec_tree	*left;
	struct s_exec_tree	*right;
}						t_exec_tree;

int	here_doc(char *delimiter);

#endif