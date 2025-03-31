/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:15:08 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/31 15:56:31 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signals.h"

static t_bool	is_valid_digit(char *str)
{
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	exit(char **args)
{
	size_t	i;

	if (args[1] == NULL)
	{
		g_received_signal = -1;
		return (ft_atoi(ft_getenv("?")));
	}
	if (!is_valid_digit(args[1]))
	{
		print_exit_error(args[1], "numeric argument required");
		g_received_signal = -1;
		return (2);
	}
	if (args[2] != NULL)
	{
		print_exit_error(args[2], "too many arguments");
		return (1);
	}
	g_received_signal = -1;
	return ((int)ft_atoui8(args[1]));
}
