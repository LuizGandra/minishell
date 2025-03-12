/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:45:52 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/12 10:58:26 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(void)
{
	const char	**env = (const char **)__environ;
	char		*key;
	char		*value;
	char		*ptr;

	get_minishell()->table = ft_map_create(12000);
	while (*env)
	{
		ptr = ft_strchr(*env, '=');
		key = ft_substr(*env, 0, ptr - *env);
		value = ft_strdup(ptr + 1);
		ft_map_insert(get_minishell()->table, key, value);
		free(key);
		free(value);
		env++;
	}
}
