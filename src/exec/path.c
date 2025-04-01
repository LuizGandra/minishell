/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:02:30 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/01 13:19:05 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*join_path(char *absolute, char *relative)
{
	return (ft_strjoin_with_free(ft_strjoin(absolute, "/"), relative));
}

static char	*search_in_path(char *cmd)
{
	char	*new_cmd;
	char	**path;
	int		i;

	i = 0;
	new_cmd = NULL;
	path = ft_split(ft_getenv("PATH"), ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		new_cmd = join_path(path[i], cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
			break ;
		free(new_cmd);
		new_cmd = NULL;
		i++;
	}
	ft_free_matrix((char **)path, free);
	return (new_cmd);
}

char	*handle_path(char *cmd)
{
	char	*new_cmd;

	new_cmd = NULL;
	if (ft_strchr(cmd, '/') == NULL)
	{
		new_cmd = search_in_path(cmd);
	}
	else
	{
		if (cmd[0] == '~')
			new_cmd = ft_strjoin(ft_getenv("HOME"), cmd + 1);
		else
			new_cmd = ft_strdup(cmd);
	}
	return (new_cmd);
}
