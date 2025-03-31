/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:54:07 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/03/27 21:25:11 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handle_signal(int signal)
{
	g_received_signal = signal;
}

void	listen_signals(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}