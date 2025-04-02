/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:19 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/02 08:41:25 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	exec_command(t_exec_tree *tree)
{
	t_token_list	*tmp;
	t_bool			first;

	tmp = tree->command;
	first = TRUE;
	while (tmp)
	{
		if (first)
			ft_printf("cmd: %s ", tmp->token.full_content);
		else
			ft_printf("%s ", tmp->token.full_content);
		first = FALSE;
		tmp = tmp->next;
	}
	ft_printf("\n");
	return (0);
}

static int	exec_pipe(t_exec_tree *tree)
{
	int	pipefd[2];
	int	pid;
	int	status;

	if (pipe(pipefd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec(tree->left);
		exit(1);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	status = exec(tree->right);
	waitpid(pid, NULL, 0);
	return (status);
}

int	exec(t_exec_tree *tree)
{
	int	result;

	if (!tree)
		return (0);
	if (tree->type == TREE_SUBSHELL)
		return (exec(tree->subshell));
	if (tree->type == TREE_PIPE)
		return (exec_pipe(tree));
	if (tree->type == TREE_COMMAND)
		return (exec_command(tree));
	result = exec(tree->left);
	if (tree->type == TREE_OR && result)
		result = exec(tree->right);
	else if (tree->type == TREE_AND && !result)
		result = exec(tree->right);
	return (result);
}
