/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:55:43 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 15:08:40 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*get_shell(void)
{
	static t_shell	shell;

	return (&shell);
}

int	*get_fd_to_close(void)
{
	static int	fd;

	return (&fd);
}

t_hash_table	**get_exported_vars(void)
{
	static t_hash_table	*exported_vars;
	char				**env;

	if (!exported_vars)
	{
		env = map_to_env(get_shell()->env);
		exported_vars = env_to_map(env);
		ft_free_matrix((void **)env, free);
	}
	return (&exported_vars);
}
