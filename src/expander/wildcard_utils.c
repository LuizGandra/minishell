/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:04:12 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 16:25:28 by lcosta-g         ###   ########.fr       */
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
