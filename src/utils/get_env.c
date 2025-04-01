/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:45:52 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/31 18:34:38 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getpid(void)
{
	int		fd;
	char	*pid;
	char	*line;

	fd = open("/proc/self/stat", O_RDONLY);
	line = get_next_line(fd);
	pid = ft_substr(line, 0, ft_strchr(line, ' ') - line);
	free(line);
	close_and_clear(fd);
	return (pid);
}

void	init_env(void)
{
	const char	**env = (const char **)__environ;
	char		*key;
	char		*value;
	char		*ptr;

	get_minishell()->env = ft_map_create(12000);
	ft_map_insert(get_minishell()->env, "?", "0");
	value = ft_getpid();
	ft_map_insert(get_minishell()->env, "$", value);
	free(value);
	while (*env)
	{
		ptr = ft_strchr(*env, '=');
		key = ft_substr(*env, 0, ptr - *env);
		value = ft_strdup(ptr + 1);
		ft_map_insert(get_minishell()->env, key, value);
		free(key);
		free(value);
		env++;
	}
}

char	*ft_getenv(char *key)
{
	t_shell	*shell;

	shell = get_minishell();
	if (!key)
		return (NULL);
	return (ft_map_search(shell->env, key));
}
