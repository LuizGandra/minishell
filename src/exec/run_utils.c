/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:37:06 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/30 12:16:29 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == -1)
		return (0);
	return ((((statbuf.st_mode) & 0170000) == (0040000)));
}

int	display_error(char *cmd)
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
		ret_code = 2;
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
