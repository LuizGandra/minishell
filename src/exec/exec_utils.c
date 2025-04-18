/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:30:18 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/18 19:00:05 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

int	exec_redirect(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool bfrk)
{
	int		redir_fds[2];
	char	*old_path;
	int		result;
	char	*path;

	redir_fds[READ_FD] = fds[READ_FD];
	redir_fds[WRITE_FD] = fds[WRITE_FD];
	old_path = ft_strdup(tree->file->token.full_content);
	expand(&tree->file, TRUE);
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
	result = exec(tree->left, redir_fds, list, bfrk);
	if (redir_fds[READ_FD] != fds[READ_FD])
		close(redir_fds[READ_FD]);
	if (redir_fds[WRITE_FD] != fds[WRITE_FD])
		close(redir_fds[WRITE_FD]);
	return (result);
}

int	exec_command(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool bfork)
{
	int	ret_code;

	dup2(fds[READ_FD], STDIN_FILENO);
	dup2(fds[WRITE_FD], STDOUT_FILENO);
	signal(SIGINT, SIG_IGN);
	expand(&tree->command, FALSE);
	ret_code = run(tree->command, list, bfork, fds);
	dup2(get_minishell()->default_fds[READ_FD], STDIN_FILENO);
	dup2(get_minishell()->default_fds[WRITE_FD], STDOUT_FILENO);
	return (ret_code);
}

int	exec_pipe(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool bfork)
{
	int	pipe_fds[2];
	int	new_fds[2];
	int	result;

	bfork = TRUE;
	pipe(pipe_fds);
	fd_list_add(pipe_fds[0]);
	fd_list_add(pipe_fds[1]);
	new_fds[READ_FD] = fds[READ_FD];
	new_fds[WRITE_FD] = pipe_fds[WRITE_FD];
	exec(tree->left, new_fds, list, bfork);
	new_fds[READ_FD] = pipe_fds[READ_FD];
	new_fds[WRITE_FD] = fds[WRITE_FD];
	result = exec(tree->right, new_fds, list, bfork);
	close(pipe_fds[WRITE_FD]);
	close(pipe_fds[READ_FD]);
	return (result);
}

int	exec_and_or(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool bfork)
{
	int			ret;
	t_pid_list	*prev;

	prev = list;
	list = create_pid_list(tree);
	ret = exec(tree->left, fds, list, bfork);
	if (ret == FORKED)
		ret = wait_pids(list);
	free_pid_list(list);
	list = prev;
	if (tree->type == TREE_OR && ret)
		ret = exec(tree->right, fds, list, bfork);
	else if (tree->type == TREE_AND && !ret)
		ret = exec(tree->right, fds, list, bfork);
	return (ft_setenv("?", ft_itoa(ret), TRUE));
}

int	exec_subshell(t_exec_tree *tree, int fds[2], t_pid_list *list, t_bool bfrk)
{
	int		status;
	int		ret;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		bfrk = FALSE;
		ret = exec(tree->subshell, fds, list, bfrk);
		clean_all();
		exit(ret);
	}
	waitpid(pid, &status, 0);
	return (get_return_value(status));
}
