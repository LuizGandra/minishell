/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:12:21 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 14:32:56 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	var = ft_calloc(3, sizeof(char *));
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
