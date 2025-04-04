/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:57 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 15:29:05 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		if (wcoredump(status))
			ft_printf_fd(2, C_RED "quit" C_RST " (core dumped)");
		return (wtermsig(status) + 128);
	}
	return (wexitstatus(status));
}
