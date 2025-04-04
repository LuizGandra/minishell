/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:19 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 12:11:42 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

static int	exec_redirect(t_exec_tree *tree, int fds[2])
{
	int	redir_fds[2];
	int	result;

	redir_fds[READ_FD] = fds[READ_FD];
	redir_fds[WRITE_FD] = fds[WRITE_FD];
	if (tree->type == TREE_REDIR_IN)
		redir_fds[READ_FD] = open(tree->file, O_R);
	else if (tree->type == TREE_REDIR_OUT)
		redir_fds[WRITE_FD] = open(tree->file, O_W | O_C | O_T, 0644);
	else if (tree->type == TREE_REDIR_APPEND)
		redir_fds[WRITE_FD] = open(tree->file, O_W | O_C | O_A, 0644);
	else if (tree->type == TREE_REDIR_HEREDOC)
		redir_fds[READ_FD] = tree->here_doc_fd;
	if (redir_fds[READ_FD] == -1)
	{
		perror(tree->file);
		return (1);
	}
	result = exec(tree->left, redir_fds);
	if (redir_fds[READ_FD] != fds[READ_FD])
		close(redir_fds[READ_FD]);
	if (redir_fds[WRITE_FD] != fds[WRITE_FD])
		close(redir_fds[WRITE_FD]);
	return (result);
}

static int	exec_command(t_exec_tree *tree, int fds[2])
{
	int	pid;
	int	status;
	int	ret_code;

	status = 0;
	dup2(fds[READ_FD], STDIN_FILENO);
	dup2(fds[WRITE_FD], STDOUT_FILENO);
	ret_code = -1;
	if (is_builtin(tree->command))
		ret_code = run_builtin(tree->command);
	else
	{
		signal(SIGINT, handle_signal);
		pid = fork();
		if (pid == 0)
			run_external(tree->command);
		waitpid(pid, &status, 0);
		signal(SIGINT, ft_rl_newline);
	}
	dup2(get_minishell()->default_fds[READ_FD], STDIN_FILENO);
	dup2(get_minishell()->default_fds[WRITE_FD], STDOUT_FILENO);
	if (ret_code == -1)
		ret_code = my_WEXITSTATUS(status);
	return (ret_code);
}

static int	exec_pipe(t_exec_tree *tree, int fds[2])
{
	int	pipe_fds[2];
	int	new_fds[2];
	int	result;

	pipe(pipe_fds);
	new_fds[READ_FD] = fds[READ_FD];
	new_fds[WRITE_FD] = pipe_fds[WRITE_FD];
	exec(tree->left, new_fds);
	close(pipe_fds[WRITE_FD]);
	new_fds[READ_FD] = pipe_fds[READ_FD];
	new_fds[WRITE_FD] = fds[WRITE_FD];
	result = exec(tree->right, new_fds);
	close(pipe_fds[READ_FD]);
	return (result);
}

static t_bool	is_redirect_type(t_tree_type type)
{
	return (type == TREE_REDIR_IN || type == TREE_REDIR_OUT
		|| type == TREE_REDIR_APPEND || type == TREE_REDIR_HEREDOC);
}

int	exec(t_exec_tree *tree, int fds[2])
{
	int	result;

	if (!tree)
		return (0);
	if (tree->type == TREE_SUBSHELL)
		return (exec(tree->subshell, fds));
	if (tree->type == TREE_PIPE)
		return (exec_pipe(tree, fds));
	if (tree->type == TREE_COMMAND)
		return (exec_command(tree, fds));
	if (is_redirect_type(tree->type))
		return (exec_redirect(tree, fds));
	result = exec(tree->left, fds);
	if (tree->type == TREE_OR && result)
		return (exec(tree->right, fds));
	else if (tree->type == TREE_AND && !result)
		return (exec(tree->right, fds));
	return (result);
}
