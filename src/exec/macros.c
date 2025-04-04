/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:55:57 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 15:06:23 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	wifexited(int status)
{
	return ((status & 0x7F) == 0);
}

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
