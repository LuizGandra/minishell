/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:56:56 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 09:48:47 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_all(void)
{
	int	ret_code;

	ret_code = (int)ft_atoui8(ft_getenv("?"));
	close(get_minishell()->default_fds[0]);
	close(get_minishell()->default_fds[1]);
	ft_map_destroy(get_minishell()->env);
	ft_gc_exit();
	return (ret_code);
}
