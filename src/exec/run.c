/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:06:59 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/09 15:20:31 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"
#include <sys/stat.h>

static int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (0);
	return ((((statbuf.st_mode) & 0170000) == (0040000)));
}

static int	display_error(char *cmd)
{
	int	ret_code;

	if (access(cmd, F_OK) != 0 || ft_strchr(cmd, '/') == NULL)
	{
		if (ft_strchr(cmd, '/') == NULL)
			ft_printf_fd(2, "%s: " CMD_NFOUND, cmd);
		else
			ft_printf_fd(2, MINISHELL "%s: " FILE_NFOUND, cmd);
		ret_code = 127;
	}
	else if (access(cmd, F_OK | X_OK) != 0 || is_directory(cmd))
	{
		ret_code = 126;
		if (is_directory(cmd))
			ft_printf_fd(2, MINISHELL "%s: " IS_A_DIR, cmd);
		else
			ft_printf_fd(2, MINISHELL "%s: " PERM_DENIED, cmd);
	}
	else
	{
		perror(cmd);
		ret_code = 1;
	}
	return (ret_code);
}

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

void	run_external(t_token_list *list)
{
	char	*path;
	char	**argv;
	char	**envp;
	int		ret_code;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ret_code = 0;
	path = handle_path(list->token.full_content);
	if (!(ft_strchr(path, '/') != NULL || access(path, F_OK | X_OK) == 0))
	{
		ret_code = display_error(path);
		// NEED CLEEN MAYBE
		exit(ret_code);
	}
	argv = handle_argv(list);
	envp = map_to_env(get_minishell()->env);
	if (execve(path, argv, envp) == -1)
	{
		ret_code = display_error(path);
		// NEED CLEEN
		exit(ret_code);
	}
}

int	run(t_token_list *command, int fds[2], t_pid_list *list,
		t_bool builtin_fork)
{
	int		ret_code;
	pid_t	pid;

	if (is_builtin(command))
	{
		if (!builtin_fork)
			ret_code = run_builtin(command);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				ret_code = run_builtin(command);
				// CLEAN_UP
				exit(ret_code);
			}
		}
	}
	else
	{
		pid = fork();
		add_pid(list, pid);
		if (pid == 0)
			run_external(command);
	}
}
