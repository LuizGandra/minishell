/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:17:54 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/03 14:40:43 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_line(counter)
{
	ft_printf(C_PUR "heredoc" C_ITA " %ith " C_RST "> ", counter);
	return (get_next_line(get_minishell()->default_fds[READ_FD]));
}
static void	write_line(char *line, int pipe_fd[2])
{
	ft_printf_fd(pipe_fd[WRITE_FD], line);
	free(line);
}
int	here_doc(char *delimiter)
{
	char	*line;
	size_t	counter;
	int		pipe_fd[2];

	counter = 0;
	line = NULL;
	pipe(pipe_fd);
	while (TRUE)
	{
		line = get_line(++counter);
		if (!line)
		{
			ft_printf_fd(2, "here_doc: (required '%s')\n", delimiter);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write_line(line, pipe_fd);
	}
	clear_gnl_buffer(get_minishell()->default_fds[READ_FD]);
	close(pipe_fd[WRITE_FD]);
	return (pipe_fd[READ_FD]);
}
