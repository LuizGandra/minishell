/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:19 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/17 08:51:43 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool builtin_fork)
{
	int	result;

	result = 0;
	if (!tree)
		return (0);
	if (tree->type == TREE_SUBSHELL)
		return (exec_subshell(tree, fds, list, builtin_fork));
	if (tree->type == TREE_PIPE)
		return (exec_pipe(tree, fds, list, builtin_fork));
	if (tree->type == TREE_CMD)
		return (exec_command(tree, fds, list, builtin_fork));
	if (tree->type == TREE_REDIR_IN || tree->type == TREE_REDIR_OUT
		|| tree->type == TREE_REDIR_OUT_APP || tree->type == TREE_REDIR_HDOC)
		return (exec_redirect(tree, fds, list, builtin_fork));
	if (tree->type == TREE_AND || tree->type == TREE_OR)
		exec_and_or(tree, fds, list, builtin_fork);
	return (result);
}
