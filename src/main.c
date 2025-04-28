/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/28 10:59:07 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexing.h"
#include "minishell.h"
#include "parser.h"
#include "signals.h"

static void	ft_loop(void);

int	main(void)
{
	init_env();
	ft_loop();
	return (clean_all());
}
static void	clone_terminal(void)
{
	t_shell	*shell;

	shell = get_minishell();
	tcgetattr(STDIN_FILENO, &shell->termios);
	shell->default_fds[READ_FD] = dup(STDIN_FILENO);
	shell->default_fds[WRITE_FD] = dup(STDOUT_FILENO);
}

static void	reset_terminal(void)
{
	t_shell	*shell;

	shell = get_minishell();
	signal(SIGINT, sig_new_line);
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios);
	dup2(shell->default_fds[READ_FD], STDIN_FILENO);
	dup2(shell->default_fds[WRITE_FD], STDOUT_FILENO);
}

void		print_tree(t_exec_tree *tree, int level);
t_exec_tree	*get_token_tree(t_token_list *token_list,
				t_tree_hierarchy hierarchy);

static void	ft_loop(void)
{
	t_shell		*shell;
	t_pid_list	*pid_list;

	listen_signals();
	clone_terminal();
	shell = get_minishell();
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
		if (!shell->tree)
		{
			ft_gc_exit();
			continue ;
		}
		print_tree(shell->tree, 0);
		pid_list = create_pid_list(shell->tree);
		exec(shell->tree, shell->default_fds, pid_list, FALSE);
		ft_setenv("?", ft_itoa(wait_pids(pid_list)), TRUE);
		free_pid_list(pid_list);
		ft_gc_exit();
	}
}
