/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:31:26 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/10 07:51:46 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

t_hash_table	*ft_map_create(size_t size)
{
	t_hash_table	*table;

	table = ft_calloc(1, sizeof(t_hash_table));
	if (!table)
		return (NULL);
	table->size = ft_next_prime(size);
	table->items = ft_calloc(table->size, sizeof(t_h_item *));
	return (table);
}
