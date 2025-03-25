/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:21:33 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/25 15:49:41 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_bool	match_wildcard(const char *pattern, const char *filename)
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

static void	expand_wildcard(t_token *token)
{
	
}