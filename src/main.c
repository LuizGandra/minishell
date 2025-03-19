/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/19 13:09:26 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "minishell.h"

static void	ft_loop(void);

int	main(void)
{
	init_env();
	ft_loop();
	handle_error(E_SUCCESS);
}

static void	ft_loop(void)
{
	t_shell	*shell;

	shell = get_minishell();
	while (TRUE)
	{
		ft_gc_exit();
		shell->user_input = readline(C_CYA "minishell$> " C_RST);
		if (!shell->user_input)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(shell->user_input);
		shell->tokens = get_token_list(shell->user_input);
	}
}
