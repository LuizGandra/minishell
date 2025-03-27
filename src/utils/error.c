/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:56:56 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/25 11:19:02 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_error error)
{
	t_shell	*shell;

	shell = get_minishell();
	if (error == E_MALLOC_FAILED)
		ft_printf("Malloc failed\n");
	ft_map_destroy(shell->env);
	ft_gc_exit();
	exit(error);
}
