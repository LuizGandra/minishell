/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_item.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:31:23 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/12 11:08:43 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"

t_h_item	*ft_item_create(char *key, char *value)
{
	t_h_item	*item;

	item = ft_calloc(1, sizeof(t_h_item));
	if (!item)
		return (NULL);
	item->key = ft_strdup(key);
	item->value = ft_strdup(value);
	return (item);
}

void	free_item(t_h_item *item)
{
	if (item)
	{
		free(item->key);
		free(item->value);
		free(item);
	}
}

void	ft_items_destroy(t_h_item *item)
{
	t_h_item	*tmp;

	while (item)
	{
		tmp = item->next;
		free_item(item);
		item = tmp;
	}
}

void	ft_print_items(t_hash_table *table)
{
	t_h_item	*item;
	size_t		i;

	i = 0;
	while (i < table->size)
	{
		item = table->items[i];
		if (item)
		{
			ft_printf(C_GRN C_BLD "Items at index " C_CYA "%i\n" C_RST, i);
			while (item)
			{
				ft_printf(
					C_PUR C_BLD "\tKey: " C_WHT "%s"
					C_PUR C_BLD " Value: " C_WHT "%s\n"
					C_RST,
					item->key, item->value);
				item = item->next;
			}
		}
		i++;
	}
}
