/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:21:33 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/29 18:28:54 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <dirent.h>

static t_bool	match_dot(char *pattern, char *file)
{
	return ((*file != '.' || *pattern == '.') && ft_strcmp(file, ".")
		&& ft_strcmp(file, ".."));
}

static t_token_list	*add_token(t_token_list **list, t_token_list *prev,
		char *str, t_bool *first)
{
	t_token_list	*new;

	new = ft_gc_malloc(sizeof(t_token_list));
	if (!prev)
	{
		new->next = (*list)->next;
		*list = new;
		new->token.type = TOK_WORD;
		new->token.full_content = ft_strdup(str);
		ft_gc_add(new->token.full_content);
		*first = FALSE;
		return (new);
	}
	if (*first)
		new->next = prev->next->next;
	else
		new->next = prev->next;
	prev->next = new;
	new->token.type = TOK_WORD;
	new->token.full_content = ft_strdup(str);
	ft_gc_add(new->token.full_content);
	*first = FALSE;
	return (new);
}

t_token_list	*expand_wildcards(t_token *token, t_token_list **list)
{
	struct dirent	*entry;
	t_token_list	*prev;
	t_bool			first;
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
		if (match_wildcard(token->full_content, entry->d_name)
			&& match_dot(token->full_content, entry->d_name))
			prev = add_token(list, prev, entry->d_name, &first);
	}
	closedir(dir);
	if (!prev || first)
		return (get_current_token(*list, token));
	return (prev);
}
