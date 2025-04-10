/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:19 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/10 09:32:44 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool builtin_fork)
{
	int	result;

	if (!tree)
		return (0);
	if (tree->type == TREE_SUBSHELL)
		return (exec_subshell(tree, fds, list, builtin_fork));
	if (tree->type == TREE_PIPE)
		return (exec_pipe(tree, fds, list, builtin_fork));
	if (tree->type == TREE_COMMAND)
		return (exec_command(tree, fds, list, builtin_fork));
	if (tree->type == TREE_REDIR_IN || tree->type == TREE_REDIR_OUT
		|| tree->type == TREE_REDIR_APPEND || tree->type == TREE_REDIR_HEREDOC)
		return (exec_redirect(tree, fds, list, builtin_fork));
	if (tree->type == TREE_AND || tree->type == TREE_OR)
		exec_and_or(tree, fds, list, builtin_fork);
	return (result);
}
