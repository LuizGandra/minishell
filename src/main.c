/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/01 09:56:58 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "signals.h"
#include "minishell.h"

int	g_received_signal;

static void	ft_loop(void);

static char	*get_type(t_token token)
{
	if (token.type == PIPE)
		return ("PIPE");
	else if (token.type == WORD)
		return ("WORD");
	else if (token.type == REDIR_IN)
		return ("REDIR_IN");
	else if (token.type == REDIR_OUT)
		return ("REDIR_OUT");
	return ("UNKNOWN");
}

static void	print_tokens(t_token_list *tokens)
{
	t_token_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		ft_printf(C_CYA "type: " C_RST "%s" C_RED " value: " C_RST "%s\n",
			get_type(tmp->token), tmp->token.full_content);
		tmp = tmp->next;
	}
}

int	main(void)
{
	init_env();
	ft_loop();
	return (clean_all());
}

static void	ft_loop(void)
{
	t_shell	*shell;

	listen_signals();
	shell = get_minishell();
	while (!shell->exit)
	{
		g_received_signal = 0;
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
		print_tokens(shell->tokens);
		ft_gc_exit();
	}
}
