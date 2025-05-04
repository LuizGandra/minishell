/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:12:21 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/03 23:58:40 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_table	*init_exported_vars(char **env)
{
	t_hash_table	*map;
	char			*key;
	char			*value;
	char			*ptr;

	map = ft_map_create(12000);
	while (*env)
	{
		ptr = ft_strchr(*env, '=');
		key = ft_substr(*env, 0, ptr - *env);
		value = ft_strdup(ptr + 1);
		ft_map_insert(map, key, value);
		free(key);
		free(value);
		env++;
	}
	return (map);
}

t_int8	ft_add_exported_var(t_hash_table *map, char *key, char *value,
		t_bool free_value)
{
	t_int8	ret;

	if (!key || !value)
		return (0);
	ft_map_insert(map, key, value);
	ret = ft_atoui8(value);
	if (free_value)
		free(value);
	return (ret);
}

char	*ft_get_exported_var(t_hash_table *map, char *key)
{
	if (!key)
		return (NULL);
	return (ft_map_search(map, key));
}
