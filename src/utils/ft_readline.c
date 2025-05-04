/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:46:01 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 13:01:19 by lhenriqu         ###   ########.fr       */
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
	char	*arrow;

	minishell = C_CYA "\n📁 ";
	minishell = ft_strjoin(minishell, ft_get_pwd());
	minishell = ft_strjoin_with_free(minishell, " \n" C_RST);
	if (ft_atoi(ft_getenv("?")))
		arrow = C_RED "❯ " C_RST;
	else
		arrow = C_GRN "❯ " C_RST;
	minishell = ft_strjoin_with_free(minishell, arrow);
	line = readline(minishell);
	free(minishell);
	return (line);
}
