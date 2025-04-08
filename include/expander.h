/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:46:18 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/07 11:49:06 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexing.h"
# include "minishell.h"

// Expand the variables and wildcards changing the token list.
void			expand(t_token_list **token_list);

// ================================= EXPANDERS ================================

// Expands the variables in the token list.
void			expand_vars(t_content_part *part);
// Expands the wildcards in the token list.
t_token_list	*expand_wildcards(t_token *token, t_token_list **list);

// ================================= UTILS ====================================

// Returns the previous token list node that contains the specified token.
t_token_list	*get_left_token(t_token_list *list, t_token *token);
// Returns the token list node that contains the specified token.
t_token_list	*get_current_token(t_token_list *list, t_token *token);
// Returns TRUE if the pattern matches the filename, otherwise FALSE.
t_bool			match_wildcard(const char *pattern, const char *filename);

#endif