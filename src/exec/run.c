/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:06:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 12:00:56 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "exec.h"

char	**handle_argv(t_token_list *list)
{
	char	*line;
	char	**argv;

	argv = NULL;
	line = ft_strdup("");
	while (list)
	{
		line = ft_strjoin_with_free(line, list->token.full_content);
		line = ft_strjoin_with_free(line, "\x11");
		list = list->next;
	}
	argv = ft_split(line, '\x11');
	free(line);
	return (argv);
}

int	run_external(t_token_list *list)
{
	char *path;
	char **argv;
	char **envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	path = handle_path(list->token.full_content);
	argv = handle_argv(list);
	envp = map_to_env(get_minishell()->env);
	return (execve(path, argv, envp));
}