/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 08:41:28 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/29 10:45:20 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int b_env(char **args) {
	t_hash_table	*env;
	char	**temp;
	int		i;

	if (args[1]) {
		ft_printf("env: too many arguments\n");
		return (1);
	}
	env = get_minishell()->env;
	temp = map_to_env(env);
	if (env->size == 0) {
		ft_printf("env: no environment variables set\n");
		return (1);
	}
	while (i < (int)env->size)
	{
		ft_printf("i: %i\n---------------\n", i);
		if (temp[i])
			ft_printf("%s\n", temp[i]);
		i++;
	}
	return (0);
}
