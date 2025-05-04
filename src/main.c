/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 10:47:46 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexing.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"

static void	ft_loop(void);
static void	init_exec(t_shell *shell);

int	main(void)
{
	init_env();
	listen_signals();
	clone_terminal();
	ft_loop();
	return (clean_all());
}

static void	init_exec(t_shell *shell)
{
	t_pid_list	*pid_list;
	int			ret;

	ret = 0;
	pid_list = NULL;
	pid_list = create_pid_list(shell->tree);
	ret = exec(shell->tree, shell->default_fds, pid_list, FALSE);
	if (ret == FORKED)
		ret = wait_pids(pid_list);
	free_pid_list(pid_list);
	ft_setenv("?", ft_itoa(ret), TRUE);
}

static void	ft_loop(void)
{
	t_shell	*shell;

	shell = get_shell();
	while (!shell->exit)
	{
		reset_terminal();
		shell->user_input = ft_readline();
		if (!shell->user_input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (shell->user_input[0] == '\0')
			continue ;
		add_history(shell->user_input);
		shell->tokens = get_token_list(shell->user_input);
		shell->tree = get_token_tree(shell->tokens, ROOT);
		if (!shell->tree || shell->heredoc_status == -1)
		{
			ft_gc_exit();
			continue ;
		}
		init_exec(shell);
		ft_gc_exit();
	}
}
