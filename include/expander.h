/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:46:18 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/26 12:53:44 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexing.h"
# include "minishell.h"

typedef struct dirent	t_entry;

void					expand_vars(t_content_part *part);
t_token_list			*expand_wildcards(t_token *token, t_token_list **list);
void					expand(t_token_list **token_list);

#endif