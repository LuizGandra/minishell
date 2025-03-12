/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/12 12:31:51 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_loop(void);

int	main(void)
{
	init_env();
	ft_loop();
	ft_map_destroy(get_minishell()->table);
}

static void	ft_loop(void)
{
	t_shell *shell;

	shell = get_minishell();
	while (TRUE)
	{
		shell->user_input = readline(C_CYA "minishell$> " C_RST);
		if (!shell->user_input)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(shell->user_input);		
	}
}