/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:17:54 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/02 21:39:10 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

static void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~0001000;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void sigint_heredoc(int sig)
{
	(void) sig;
	ft_printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	signal_here_doc(int sig)
{
	close(*get_fd_to_close());
	clean_all();
	exit(128 + sig);
}

static void	run_here_doc(char *delimiter, int pipe_fd[2])
{
	char	*line;
	size_t	counter;

	counter = 0;
	signal(SIGINT, signal_here_doc);
	disable_echoctl();
	while (TRUE)
	{
		ft_printf(C_PUR "heredoc" C_ITA " %ith" C_RST "> ", ++counter);
		line = get_next_line(get_shell()->default_fds[READ_FD]);
		if (!line)
		{
			ft_printf_fd(2, C_CYA "\nhere_doc: "C_RST EOF_ERR, delimiter);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(line) - 1))
		{
			free(line);
			break ;
		}
		ft_printf_fd(pipe_fd[WRITE_FD], line);
		free(line);
	}
	clean_all();
}

int	here_doc(char *delimiter)
{
	pid_t	pid;
	int		ret;
	int		status;
	int		pipe_fd[2];

	status = 0;
	pipe(pipe_fd);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[READ_FD]);
		*get_fd_to_close() = pipe_fd[WRITE_FD];
		run_here_doc(delimiter, pipe_fd);
		close(*get_fd_to_close());
		exit(0);
	}
	signal(SIGINT, sigint_heredoc);
	close(pipe_fd[WRITE_FD]);
	waitpid(pid, &status, 0);
	ret = get_return_value(status);
	if (ret == 0)
		return (pipe_fd[READ_FD]);
	ft_setenv("?", ft_itoa(ret), TRUE);
	close(pipe_fd[READ_FD]);
	return (-1);
}
