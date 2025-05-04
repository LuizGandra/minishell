/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:12:21 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 00:22:57 by lcosta-g         ###   ########.fr       */
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

void	sort_env(char **map)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (map[i])
	{
		j = i + 1;
		while (map[j])
		{
			if (ft_strcmp(map[i], map[j]) > 0)
			{
				temp = map[i];
				map[i] = map[j];
				map[j] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**get_key_and_value(char *arg)
{
	char	*ptr;
	char	**var;

	var = ft_calloc(2, sizeof(char *));
	if (!var)
		return (NULL);
	ptr = ft_strchr(arg, '=');
	if (ptr)
	{
		var[0] = ft_substr(arg, 0, ptr - arg);
		var[1] = ft_strdup(ptr + 1);
	}
	else
	{
		var[0] = ft_strdup(arg);
		var[1] = NULL;
	}
	return (var);
}
