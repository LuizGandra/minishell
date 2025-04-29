/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:15:08 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 09:15:16 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exit_error(char *str, char *error)
{
	if (str == NULL)
		ft_printf_fd(2, MINISHELL "exit: %s\n", error);
	else
		ft_printf_fd(2, MINISHELL "exit: "C_YEL"%s"C_RST": %s\n", str, error);
}

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

int	b_exit(char **args)
{
	t_shell	*shell;

	shell = get_minishell();
	if (args[1] == NULL)
	{
		shell->exit = TRUE;
		return (ft_atoi(ft_getenv("?")));
	}
	if (!is_valid_digit(args[1]))
	{
		print_exit_error(args[1], C_RED "numeric argument required" C_RST);
		shell->exit = TRUE;
		return (2);
	}
	if (args[2] != NULL)
	{
		print_exit_error(NULL, C_RED "too many arguments" C_RST);
		return (1);
	}
	shell->exit = TRUE;
	return ((int)ft_atoui8(args[1]));
}
