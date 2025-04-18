/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:02:15 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/18 16:58:07 by lcosta-g         ###   ########.fr       */
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

	ft_printf("lst->token.full_content: %s\n", lst->token.full_content);
	if (lst->prev)
		ft_printf("lst->token->prev.full_content: %s\n", lst->prev->token.full_content);
	if (lst->next)
		ft_printf("lst->token->next.full_content: %s\n", lst->next->token.full_content);

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
	ft_printf("\nft_sublist recebeu a lista: ");
	print_token_list(lst);

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
