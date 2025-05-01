/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:37:23 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/30 15:34:36 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

static char	*handle_cd_path(int argc, char **args);
static void	print_cd_error(char *cd_path);
static char	*get_pwd(void);

int	b_cd(char **args)
{
	char	*path;
	char	*oldpwd;
	int		argc;

	argc = 0;
	while (args[argc])
		argc++;
	path = handle_cd_path(argc, args);
	if (!path)
		return (1);
	oldpwd = get_pwd();
	if (chdir(path) == -1)
	{
		print_cd_error(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	ft_setenv("OLDPWD", oldpwd, TRUE);
	free(path);
	ft_setenv("PWD", get_pwd(), TRUE);
	return (0);
}

static char	*handle_cd_path(int argc, char **args)
{
	char	*path;
	char	*home;

	if (argc > 2)
	{
		ft_printf_fd(2, MINISHELL "cd: " C_RED "too many arguments\n" C_RST);
		return (NULL);
	}
	path = NULL;
	if (argc == 1 || (argc == 2 && !ft_strcmp(args[1], "~")))
	{
		home = ft_getenv("HOME");
		if (!home || home[0] == '\0')
		{
			ft_printf_fd(2, MINISHELL "cd: " C_RED "HOME not set\n" C_RST);
			return (NULL);
		}
		path = ft_strdup(home);
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

static void	print_cd_error(char *path)
{
	if (access(path, F_OK) == -1)
		ft_printf_fd(2, MINISHELL "cd: " C_YEL "%s" C_RST ": " FILE_NFOUND,
			path);
	else if (!is_directory(path))
		ft_printf_fd(2, MINISHELL "cd: " C_YEL "%s" C_RST ": " NOT_A_DIR, path);
	else
		ft_printf_fd(2, MINISHELL "cd: " C_YEL "%s" C_RST ": " PERM_DENIED,
			path);
}

static char	*get_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup(ft_getenv("PWD"));
	if (!cwd)
		cwd = ft_strdup("");
	return (cwd);
}
