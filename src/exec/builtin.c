/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:23:10 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 09:08:07 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	build(t_builtin *builtin, t_token_list *command)
{
	char	**args;
	int		ret;

	args = handle_argv(command);
	ret = builtin(args);
	ft_free_matrix((void **)args, free);
	return (ret);
}

t_bool	is_builtin(t_token_list *command)
{
	if (ft_strcmp(command->token.full_content, "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(command->token.full_content, "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(command->token.full_content, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int	run_builtin(t_token_list *command)
{
	if (ft_strcmp(command->token.full_content, "echo") == 0)
		return (build(&b_echo, command));
	else if (ft_strcmp(command->token.full_content, "pwd") == 0)
		return (build(&b_pwd, command));
	else if (ft_strcmp(command->token.full_content, "exit") == 0)
		return (build(&b_exit, command));
	return (-1);
}