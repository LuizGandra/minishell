/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:21:33 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/26 15:49:27 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <dirent.h>

static t_bool	match_wildcard(const char *pattern, const char *filename)
{
	if (*filename == '.')
		return (FALSE);
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

static t_token_list	*get_left_token(t_token_list *list, t_token *token)
{
	t_token_list	*prev;

	prev = NULL;
	while (list)
	{
		if (token == &list->token)
			break ;
		prev = list;
		list = list->next;
	}
	return (prev);
}

static t_token_list	*get_current_token(t_token_list *list, t_token *token)
{
	while (list)
	{
		if (token == &list->token)
			return (list);
		list = list->next;
	}
	return (NULL);
}

static t_token_list	*add_token(t_token_list **list, t_token_list *prev,
		char *str, t_bool *first)
{
	t_token_list	*new;

	new = ft_gc_malloc(sizeof(t_token_list));
	if (!prev)
	{
		new->next = *list;
		*list = new;
		new->token.type = WORD;
		new->token.full_content = ft_strdup(str);
		ft_gc_add(new->token.full_content);
		return (new);
	}
	if (*first)
		new->next = prev->next->next;
	else
		new->next = prev->next;
	prev->next = new;
	new->token.type = WORD;
	new->token.full_content = ft_strdup(str);
	ft_gc_add(new->token.full_content);
	*first = FALSE;
	return (new);
}

t_token_list	*expand_wildcards(t_token *token, t_token_list **list)
{
	t_bool			first;
	t_token_list	*prev;
	t_entry			*entry;
	DIR				*dir;

	first = TRUE;
	if (!ft_strchr(token->full_content, '\x11'))
		return (get_current_token(*list, token));
	dir = opendir(".");
	if (!dir)
		return (get_current_token(*list, token));
	prev = get_left_token(*list, token);
	while (TRUE)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (match_wildcard(token->full_content, entry->d_name))
			prev = add_token(list, prev, entry->d_name, &first);
	}
	closedir(dir);
	if (!prev)
		return ((get_current_token(*list, token)));
	return (prev);
}
