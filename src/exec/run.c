/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:06:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/17 08:40:48 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "signals.h"

void	run_external(t_token_list *command, t_pid_list *list)
{
	char	*path;
	char	**argv;
	char	**envp;
	int		ret_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ret_code = 0;
	path = handle_path(command->token.full_content);
	if (!(ft_strchr(path, '/') != NULL || access(path, F_OK | X_OK) == 0))
	{
		ret_code = display_error(path);
		free_pid_list(list);
		clean_all();
		exit(ret_code);
	}
	argv = handle_argv(command);
	envp = map_to_env(get_minishell()->env);
	if (execve(path, argv, envp) == -1)
	{
		ret_code = display_error(path);
		free_pid_list(list);
		clean_all();
		exit(ret_code);
	}
}

static pid_t	ft_fork(t_pid_list *list)
{
	pid_t	pid;

	pid = fork();
	add_pid(list, pid);
	return (pid);
}

int	run(t_token_list *command, t_pid_list *list, t_bool bfork)
{
	int		ret_code;

	ret_code = FORKED;
	if (is_builtin(command))
	{
		if (!bfork)
			ret_code = run_builtin(command);
		else
		{
			if (ft_fork(list) == 0)
			{
				ret_code = run_builtin(command);
				free_pid_list(list);
				clean_all();
				exit(ret_code);
			}
		}
	}
	else
	{
		if (ft_fork(list) == 0)
			run_external(command, list);
	}
	return (ret_code);
}
