/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:57 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/03 16:05:40 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	my_WIFEXITED(int status)
{
	return ((status & 0x7F) == 0);
}

int	my_WEXITSTATUS(int status)
{
	return ((status >> 8) & 0xFF);
}

int	my_WIFSIGNALED(int status)
{
	return ((status & 0x7F) > 0 && (status & 0x7F) < 0x7F);
}

int	my_WTERMSIG(int status)
{
	return (status & 0x7F);
}
