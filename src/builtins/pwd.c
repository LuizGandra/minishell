/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:39:25 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 08:53:03 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_pwd(char **args)
{
	char	cwd[4096];

	(void)args;
	if (!getcwd(cwd, 4096))
		return (1);
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
