/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:31:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 18:49:27 by lhenriqu         ###   ########.fr       */
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
	if (fds[READ_FD] == -1)
	{
		ft_printf_fd(2, MINISHELL "%s: " FILE_NFOUND, file);
		return (1);
	}
	return (0);
}
