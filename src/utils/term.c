/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:49:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/02 21:18:48 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "signals.h"

void	clone_terminal(void)
{
	t_shell	*shell;

	shell = get_shell();
	tcgetattr(STDIN_FILENO, &shell->termios);
	shell->default_fds[READ_FD] = dup(STDIN_FILENO);
	shell->default_fds[WRITE_FD] = dup(STDOUT_FILENO);
}

void	reset_terminal(void)
{
	t_shell	*shell;

	shell = get_shell();
	shell->heredoc_status = 0;
	signal(SIGINT, sig_new_line);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios);
	dup2(shell->default_fds[READ_FD], STDIN_FILENO);
	dup2(shell->default_fds[WRITE_FD], STDOUT_FILENO);
}
