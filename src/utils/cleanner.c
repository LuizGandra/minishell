/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:56:56 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 15:28:10 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec.h"

int	clean_all(void)
{
	int	ret_code;

	clear_gnl_buffer(get_shell()->default_fds[READ_FD]);
	ret_code = (int)ft_atoui8(ft_getenv("?"));
	close(get_shell()->default_fds[0]);
	close(get_shell()->default_fds[1]);
	ft_map_destroy(*get_exported_vars());
	ft_map_destroy(get_shell()->env);
	ft_gc_exit();
	return (ret_code);
}
