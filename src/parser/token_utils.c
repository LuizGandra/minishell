/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:02:15 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 19:09:04 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_lstlast(t_token_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static t_token_list	*ft_nodecpy(t_token_list *lst)
{
	t_token_list	*node;

	node = ft_gc_malloc(sizeof(t_token_list));
	ft_memmove(&node->token, &lst->token, sizeof(t_token));
	if (lst->token.full_content)
		node->token.full_content = ft_strdup(lst->token.full_content);
	ft_gc_add(node->token.full_content);
	return (node);
}

t_token_list	*ft_sublist(t_token_list *lst, t_token_list *start,
		t_token_list *end)
{
	t_token_list	*sublist;
	t_token_list	*tail;
	t_token_list	*node;

	sublist = NULL;
	tail = NULL;
	while (lst && lst != start)
		lst = lst->next;
	while (lst && lst != end)
	{
		node = ft_nodecpy(lst);
		if (!node)
			return (NULL);
		// ft_memmove(&node->file, &lst->file, sizeof(t_token_list)); // CORRIGIR SEGFAULT NO GC_MALLOC
		if (!sublist)
			sublist = node;
		else
		{
			tail->next = node;
			node->prev = tail;
		}
		tail = node;
		lst = lst->next;
	}
	return (sublist);
}
