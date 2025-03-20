/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:56:56 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/19 13:00:15 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_error error)
{
	if (error == E_MALLOC_FAILED)
		ft_printf("Malloc failed\n");
	ft_map_destroy(get_minishell()->table);
	ft_gc_exit();
	exit(error);
}
