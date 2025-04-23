/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:29:58 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/18 18:31:33 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FD_LIST_H
# define FD_LIST_H

typedef struct s_fd_list
{
	int					fd;
	struct s_fd_list	*next;
}						t_fd_list;

#endif
