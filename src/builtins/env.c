/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:41:28 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 15:25:38 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(char **args)
{
	char	**tmp;
	char	**env;
	char	*str;

	if (args[1])
	{
		ft_printf_fd(2, MINISHELL "env: " C_RED "too many arguments\n" C_RST);
		return (1);
	}
	env = map_to_env(get_shell()->env);
	tmp = env;
	while (tmp)
	{
		str = *tmp;
		if (!str)
			break ;
		ft_printf("%s\n", str);
		tmp++;
	}
	ft_free_matrix((void **)env, free);
	return (0);
}
