/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:28:05 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/27 14:37:22 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	t_bool	n_flag;
	int		i;

	i = 1;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		i++;
		n_flag = TRUE;
	}
	while (args[i] != NULL)
	{
		ft_putstr(args[i]);
		if (args[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	if (!n_flag)
		ft_putstr("\n");
	return (0);
}
