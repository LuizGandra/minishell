/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:31:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 00:32:01 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	expand_file(t_exec_tree *tree)
{
	char	*old_path;

	old_path = ft_strdup(tree->file->token.full_content);
	expand(&tree->file);
	if (tree->file->next)
	{
		ft_printf_fd(2, MINISHELL "%s: " AMBIG_REDIR, old_path);
		free(old_path);
		return (FALSE);
	}
	free(old_path);
	return (TRUE);
}

static void	print_file_error(char *file)
{
	if (access(file, F_OK) == -1)
		ft_printf_fd(2, MINISHELL "%s: " FILE_NFOUND, file);
	else if (is_directory(file))
		ft_printf_fd(2, MINISHELL "%s: " IS_A_DIR, file);
	else
		ft_printf_fd(2, MINISHELL "%s: " PERM_DENIED, file);
}

int	open_file(char *file, int fds[2], t_tree_type type, int heredoc_fd)
{
	if (type == TREE_REDIR_IN)
		fds[READ_FD] = open(file, O_R);
	else if (type == TREE_REDIR_OUT)
		fds[WRITE_FD] = open(file, O_W | O_C | O_T, 0644);
	else if (type == TREE_REDIR_OUT_APP)
		fds[WRITE_FD] = open(file, O_W | O_C | O_A, 0644);
	else if (type == TREE_REDIR_HDOC)
		fds[READ_FD] = heredoc_fd;
	if (fds[READ_FD] == -1 || fds[WRITE_FD] == -1)
	{
		print_file_error(file);
		return (1);
	}
	return (0);
}
