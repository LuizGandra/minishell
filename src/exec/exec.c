/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:19 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/09 15:16:59 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

static int	open_file(char *file, int fds[2], t_tree_type type, int heredoc_fd)
{
	if (type == TREE_REDIR_IN)
		fds[READ_FD] = open(file, O_R);
	else if (type == TREE_REDIR_OUT)
		fds[WRITE_FD] = open(file, O_W | O_C | O_T, 0644);
	else if (type == TREE_REDIR_APPEND)
		fds[WRITE_FD] = open(file, O_W | O_C | O_A, 0644);
	else if (type == TREE_REDIR_HEREDOC)
		fds[READ_FD] = heredoc_fd;
	if (fds[READ_FD] == -1)
	{
		ft_printf_fd(2, MINISHELL "%s: " FILE_NFOUND, file);
		return (1);
	}
	return (0);
}

static int	exec_redirect(t_exec_tree *tree, int fds[2], t_pid_list *list,
		t_bool builtin_fork)
{
	int		redir_fds[2];
	char	*old_path;
	int		result;
	char	*path;

	redir_fds[READ_FD] = fds[READ_FD];
	redir_fds[WRITE_FD] = fds[WRITE_FD];
	old_path = ft_strdup(tree->file->token.full_content);
	expand(&tree->file);
	if (tree->file->next)
	{
		ft_printf_fd(2, MINISHELL "%s: " AMBIG_REDIR, old_path);
		free(old_path);
		return (1);
	}
	free(old_path);
	path = tree->file->token.full_content;
	if (open_file(path, redir_fds, tree->type, tree->here_doc_fd))
		return (1);
	result = exec(tree->left, redir_fds, list, builtin_fork);
	if (redir_fds[READ_FD] != fds[READ_FD])
		close(redir_fds[READ_FD]);
	if (redir_fds[WRITE_FD] != fds[WRITE_FD])
		close(redir_fds[WRITE_FD]);
	return (result);
}

static int	exec_command(t_exec_tree *tree, int fds[2], t_pid_list *list,
		t_bool builtin_fork)
{
	int	ret_code;

	dup2(fds[READ_FD], STDIN_FILENO);
	dup2(fds[WRITE_FD], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	expand(&tree->command);
	ret_code = run(tree->command, fds, list, builtin_fork);
	dup2(get_minishell()->default_fds[READ_FD], STDIN_FILENO);
	dup2(get_minishell()->default_fds[WRITE_FD], STDOUT_FILENO);
	return (ret_code);
}

static int	exec_pipe(t_exec_tree *tree, int fds[2], t_pid_list *list,
		t_bool builtin_fork)
{
	int	pipe_fds[2];
	int	new_fds[2];
	int	result;

	builtin_fork = TRUE;
	pipe(pipe_fds);
	new_fds[READ_FD] = fds[READ_FD];
	new_fds[WRITE_FD] = pipe_fds[WRITE_FD];
	exec(tree->left, new_fds, list, builtin_fork);
	new_fds[READ_FD] = pipe_fds[READ_FD];
	new_fds[WRITE_FD] = fds[WRITE_FD];
	result = exec(tree->right, new_fds, list, builtin_fork);
	close(pipe_fds[WRITE_FD]);
	close(pipe_fds[READ_FD]);
	return (result);
}

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

int	exec_and_or(t_exec_tree *tree, int fds[2], t_pid_list *list,
		t_bool builtin_fork)
{
	int		ret;
	pid_t	pid;

	list = create_pid_list(tree);
	ret = exec(tree->left, fds, list, builtin_fork);
	if (ret == NOT_BUILTIN)
		ret = wait_pids(list);
	free_pid_list(list);
	if (tree->type == TREE_OR && ret)
		ret = exec(tree->right, fds, list, builtin_fork);
	else if (tree->type == TREE_AND && !ret)
		ret = exec(tree->right, fds, list, builtin_fork);
	return (ft_setenv("?", ft_itoa(ret), TRUE));
}

int	exec_subshell(t_exec_tree *tree, int fds[2], t_pid_list *list,
		t_bool builtin_fork)
{
	int		status;
	int		ret;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		builtin_fork = FALSE;
		ret = exec(tree->subshell, fds, list, builtin_fork);
		exit(ret);
	}
	waitpid(pid, &status, 0);
	return (get_return_value(status));
}
