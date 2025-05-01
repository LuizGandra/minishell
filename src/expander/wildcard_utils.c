/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:04:12 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 18:29:05 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_bool	match_wildcard(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (TRUE);
	if (*pattern == '\x11')
	{
		return (match_wildcard(pattern + 1, filename) || (*filename
				&& match_wildcard(pattern, filename + 1)));
	}
	if (*pattern == *filename)
		return (match_wildcard(pattern + 1, filename + 1));
	return (FALSE);
}

t_token_list	*get_left_token(t_token_list *list, t_token *token)
{
	t_token_list	*prev;

	prev = NULL;
	while (list->next)
	{
		if (token == &list->token)
			break ;
		prev = list;
		list = list->next;
	}
	return (prev);
}

t_token_list	*get_current_token(t_token_list *list, t_token *token)
{
	while (list)
	{
		if (token == &list->token)
			return (list);
		list = list->next;
	}
	return (NULL);
}
