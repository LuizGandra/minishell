/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:45:52 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/03 19:44:02 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(void)
{
	t_shell	*shell;

	shell = get_shell();
	shell->env = env_to_map(__environ);
	ft_setenv("?", "0", FALSE);
	ft_setenv("$", ft_getpid(), TRUE);
}

t_hash_table	*env_to_map(char **env)
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

char	**map_to_env(t_hash_table *map)
{
	char		**env;
	t_h_item	*tmp;
	size_t		i_env;
	int			i;

	i = -1;
	i_env = 0;
	env = NULL;
	while (++i < (int)map->size)
	{
		tmp = map->items[i];
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "?") && ft_strcmp(tmp->key, "$"))
			{
				env = ft_recalloc(env, sizeof(char *) * (i_env + 2),
						sizeof(char *) * (i_env + 1));
				env[i_env] = ft_strjoin(tmp->key, "=");
				env[i_env] = ft_strjoin_with_free(env[i_env], tmp->value);
				i_env++;
			}
			tmp = tmp->next;
		}
	}
	return (env);
}

t_int8	ft_setenv(char *key, char *value, t_bool free_value)
{
	t_shell	*shell;
	t_int8	ret;

	shell = get_shell();
	if (!key || !value)
		return (0);
	ft_map_insert(shell->env, key, value);
	ret = ft_atoui8(value);
	if (free_value)
		free(value);
	return (ret);
}

char	*ft_getenv(char *key)
{
	t_shell	*shell;

	shell = get_shell();
	if (!key)
		return (NULL);
	return (ft_map_search(shell->env, key));
}
