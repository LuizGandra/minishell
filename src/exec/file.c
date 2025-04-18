/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:31:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/17 08:51:43 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
