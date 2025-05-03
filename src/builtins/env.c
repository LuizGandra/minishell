/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:41:28 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/02 20:10:22 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(char **args)
{
	char	**temp;
	char	*str;

	if (args[1])
	{
		ft_printf_fd(2, MINISHELL "env: " C_RED "too many arguments\n" C_RST);
		return (1);
	}
	temp = map_to_env(get_shell()->env);
	while (temp)
	{
		str = *temp;
		if (!str)
			break ;
		ft_printf("%s\n", str);
		temp++;
	}
	return (0);
}
