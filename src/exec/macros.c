/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:57 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/07 12:28:39 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <signal.h>

int	wexitstatus(int status)
{
	return ((status >> 8) & 0xFF);
}

int	wifsignaled(int status)
{
	return ((status & 0x7F) > 0 && (status & 0x7F) < 0x7F);
}

int	wtermsig(int status)
{
	return (status & 0x7F);
}

int	wcoredump(int status)
{
	return ((status & 0x80) != 0);
}

int	get_return_value(int status)
{
	if (wifsignaled(status))
	{
		if (wtermsig(status) == SIGQUIT)
			ft_printf_fd(2, C_RED "Quit" C_RST);
		else if (wtermsig(status) == SIGKILL)
			ft_printf_fd(2, C_RED "Killed" C_RST);
		else if (wtermsig(status) == SIGSTOP)
			ft_printf_fd(2, C_RED "Stopped" C_RST);
		else if (wtermsig(status) == SIGABRT)
			ft_printf_fd(2, C_RED "Aborted" C_RST);
		else if (wtermsig(status) == SIGSEGV)
			ft_printf_fd(2, C_RED "Segmentation fault" C_RST);
		else if (wtermsig(status) == SIGFPE)
			ft_printf_fd(2, C_RED "Floating point exception" C_RST);
		else if (wtermsig(status) == SIGXFSZ)
			ft_printf_fd(2, C_RED "File size limit exceeded" C_RST);
		if (wcoredump(status))
			ft_printf_fd(2, " (core dumped)");
		return (wtermsig(status) + 128);
	}
	return (wexitstatus(status));
}
