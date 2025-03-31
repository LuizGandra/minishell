/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:02:15 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/31 11:19:36 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	ft_lstsize(t_token_list *lst)
{
	size_t	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

static t_token_list	*ft_nodecpy(t_token_list *lst)
{
	t_token_list	*node;

	node = ft_gc_malloc(sizeof(t_token_list));
	ft_memmove(&node->token, &lst->token, sizeof(t_token));
	node->token.full_content = ft_strdup(lst->token.full_content);
	ft_gc_add(node->token.full_content);
	return (node);
}

t_token_list	*ft_sublist(t_token_list *lst, size_t start, size_t len)
{
	t_token_list	*sublist;
	t_token_list	*node;
	t_token_list	*prev;
	size_t			i;

	i = 0;
	sublist = NULL;
	while (lst && len)
	{
		if (++i >= (start + 1))
		{
			node = ft_nodecpy(lst);
			if (!sublist)
				sublist = node;
			else
			{
				prev->next = node;
				node->prev = prev;
			}
			prev = node;
			len--;
		}
		lst = lst->next;
	}
	return (sublist);
}
