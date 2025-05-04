/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:23:10 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/02 19:53:14 by lcosta-g         ###   ########.fr       */
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
	else if (ft_strcmp(command->token.full_content, "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(command->token.full_content, "env") == 0)
		return (TRUE);
	else if (ft_strcmp(command->token.full_content, "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(command->token.full_content, "export") == 0)
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
	else if (ft_strcmp(command->token.full_content, "cd") == 0)
		return (build(&b_cd, command));
	else if (ft_strcmp(command->token.full_content, "env") == 0)
		return (build(&b_env, command));
	else if (ft_strcmp(command->token.full_content, "unset") == 0)
		return (build(&b_unset, command));
	else if (ft_strcmp(command->token.full_content, "export") == 0)
		return (build(&b_export, command));
	return (-1);
}
