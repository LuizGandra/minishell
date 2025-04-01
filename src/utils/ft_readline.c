/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:46:01 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/01 11:07:39 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_pwd(void)
{
	char	*tmp;
	char	*pwd;
	char	*home;

	tmp = NULL;
	pwd = ft_getenv("PWD");
	home = ft_getenv("HOME");
	if (ft_strncmp(pwd, home, ft_strlen(home)) == 0)
		tmp = ft_strjoin("~", pwd + ft_strlen(home));
	else
		tmp = ft_strdup(pwd);
	ft_gc_add(tmp);
	return (tmp);
}

char	*ft_readline(void)
{
	char	*line;
	char	*minishell;

	minishell = C_CYA "\n📁 ";
	minishell = ft_strjoin(minishell, ft_get_pwd());
	minishell = ft_strjoin_with_free(minishell, " \n" C_RST);
	if (ft_atoi(ft_getenv("?")))
		minishell = ft_strjoin_with_free(minishell, C_RED "❯ " C_RST);
	else
		minishell = ft_strjoin_with_free(minishell, C_GRN "❯ " C_RST);
	line = readline(minishell);
	free(minishell);
	return (line);
}
