/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:37:23 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/29 17:54:14 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*validate_args(char **args);
static void	print_cd_error(char *path);

int b_cd(char **args) {
	char	*path;
	char	*oldpwd;

	path = validate_args(args);
	if (!path)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		oldpwd = ft_getenv("PWD");
	if (chdir(path) == -1)
	{
		print_cd_error(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	ft_setenv("OLDPWD", oldpwd, TRUE);
	free(path);
	path = getcwd(NULL, 0);
	ft_setenv("PWD", path, TRUE);
	return (0);
}

static char	*validate_args(char **args)
{
	char	*path;

	path = NULL;
	if (args[2]) {
		ft_printf("cd: too many arguments\n");
		return (NULL);
	}
	if (!args[1])
		path = ft_strdup(ft_getenv("HOME"));
	else
		path = ft_strdup(args[1]);
	if (!path[0])
	{
		ft_printf("cd: HOME not set\n");
		free(path);
		return (NULL);
	}
	return (path);
}

static void	print_cd_error(char *path)
{
	char	*default_error_msg[2];
	char	*error_msg;

	default_error_msg[0] = "cd: ";
	default_error_msg[1] = ": No such file or directory";
	error_msg = ft_strjoin(default_error_msg[0], path);
	error_msg = ft_strjoin_with_free(error_msg, default_error_msg[1]);
	ft_printf("%s\n", error_msg);
}
