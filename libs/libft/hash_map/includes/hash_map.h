/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:33:39 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/10 07:53:14 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_MAP_H
# define HASH_MAP_H

# include "../../libft.h"

// A Linked list item with a key and a value
typedef struct s_h_item
{
	char			*key;
	char			*value;
	struct s_h_item	*next;
}					t_h_item;

// A Hash table with a size and a pointer to an array of items
typedef struct s_hash_table
{
	t_h_item		**items;
	size_t			size;
	size_t			count;
}					t_hash_table;

// Generate a hash up to a certain size
unsigned long int	ft_hash(const char *key, size_t size);
// Create a new hash map
t_hash_table		*ft_map_create(size_t size);
// Insert a new item in a table
void				ft_map_insert(t_hash_table *table, char *key, char *value);
// Search for an item in a table
char				*ft_map_search(t_hash_table *table, char *key);
// Delete an item in a table
void				ft_map_delete(t_hash_table *table, char *key);
// Destroy a table with all its items
void				ft_map_destroy(t_hash_table *table);
// Print all items in a table with ft_printf
void				ft_print_items(t_hash_table *table);

#endif