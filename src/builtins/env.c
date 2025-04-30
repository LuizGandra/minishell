/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:41:28 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/30 12:55:18 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_env(char **args)
{
	t_hash_table	*env;
	char			**temp;
	int				i;

	if (args[1])
	{
		ft_printf("env: too many arguments\n");
		return (1);
	}
	env = get_minishell()->env;
	temp = map_to_env(env);
	if (env->size == 0)
	{
		ft_printf("env: no environment variables set\n");
		return (1);
	}
	i = 0;
	while (i < (int)env->size)
	{
		ft_printf("i: %i\n---------------\n", i);
		if (temp[i])
			ft_printf("%s\n", temp[i]);
		i++;
	}
	return (0);
}
