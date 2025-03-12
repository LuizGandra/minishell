/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 07:47:06 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/10 07:52:49 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_UTILS_H
# define HASH_UTILS_H

# include "hash_map.h"

// Create a new item
t_h_item			*ft_item_create(char *key, char *value);

// Destroy a linked list of items
void				ft_items_destroy(t_h_item *item);

// free a single item
void				free_item(t_h_item *item);

#endif