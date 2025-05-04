/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:49:11 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/04 16:46:50 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "fd_list.h"

static t_fd_list	*get_fd_list(void)
{
	static t_fd_list	fd_list;

	return (&fd_list);
}

void	fd_list_add(int fd)
{
	t_fd_list	*list;

	list = get_fd_list();
	while (list->next)
		list = list->next;
	list->fd = fd;
	list->next = ft_gc_malloc(sizeof(t_fd_list));
}

void	fd_list_close(void)
{
	t_fd_list	*list;
	t_fd_list	*tmp;

	list = get_fd_list();
	while (list->next)
	{
		close(list->fd);
		tmp = list->next;
		list->fd = tmp->fd;
		list->next = tmp->next;
		ft_gc_free(tmp);
	}
	get_fd_list()->fd = 0;
	get_fd_list()->next = NULL;
}
