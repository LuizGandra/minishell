/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:29:34 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/07 15:58:50 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_map.h"
#include "hash_utils.h"

unsigned long int	ft_hash(const char *key, size_t size)
{
	unsigned long int	hash;
	const char			*ptr;

	if (!key)
		return (0);
	ptr = key;
	hash = 2166136261u;
	while (*ptr)
	{
		hash ^= (unsigned char)(*ptr);
		hash *= 16777619u;
		ptr++;
	}
	return (hash % size);
}

void	ft_map_insert(t_hash_table *table, char *key, char *value)
{
	unsigned long int	hash;
	t_h_item			*tmp;
	t_h_item			*prev;

	hash = ft_hash(key, table->size);
	if (!table->items[hash])
	{
		table->items[hash] = ft_item_create(key, value);
		table->count++;
		return ;
	}
	tmp = table->items[hash];
	while (tmp)
	{
		if (tmp->key && !ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = ft_item_create(key, value);
	table->count++;
}

char	*ft_map_search(t_hash_table *table, char *key)
{
	unsigned long int	hash;
	t_h_item			*tmp;

	hash = ft_hash(key, table->size);
	tmp = table->items[hash];
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_map_delete(t_hash_table *table, char *key)
{
	unsigned long int	hash;
	t_h_item			*tmp;
	t_h_item			*prev;

	hash = ft_hash(key, table->size);
	tmp = table->items[hash];
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				table->items[hash] = tmp->next;
			free_item(tmp);
			table->count--;
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_map_destroy(t_hash_table *table)
{
	size_t		i;
	t_h_item	*tmp;
	t_h_item	*next;

	i = 0;
	while (i < table->size)
	{
		tmp = table->items[i];
		while (tmp)
		{
			next = tmp->next;
			free_item(tmp);
			tmp = next;
		}
		i++;
	}
	free(table->items);
	free(table);
}
