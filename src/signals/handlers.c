/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:54:07 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/04 12:11:52 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	ft_rl_newline(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signal(int signal)
{
	g_received_signal = signal;
}

void	listen_signals(void)
{
	signal(SIGINT, ft_rl_newline);
	signal(SIGQUIT, handle_signal);
}
