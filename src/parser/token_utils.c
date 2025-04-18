/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:02:15 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/17 12:37:32 by lcosta-g         ###   ########.fr       */
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
	// ! vi dnv e acho q n é isso n kkk, acho que essa func tá fazendo a sublist errada mesmo
	// TODO pelo que eu entendi eu to passando a sublist errada, por algum motivo q eu n sei
	// TODO ela tá iniciando do ls e indo até o &&, ao invés de iniciar do cat normalmente
	// TODO preciso entender o pq disso
	ft_printf("ft_sublist recebeu a lista: ");
	print_token_list(lst);
	ft_printf("start: %s, end: %s\n",
		start ? start->token.full_content : "NULL",
		end ? end->token.full_content : "NULL");

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
			tail->next = node;
		tail = node;
		lst = lst->next;
	}
	return (sublist);
}
