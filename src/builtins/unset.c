/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:33:40 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/05/04 00:28:44 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(char **args)
{
	t_hash_table	*env;
	char			**temp;
	char			*str;

	if (!args || !args[1])
		return (0);
	env = get_minishell()->env;
	temp = &args[1];
	while (*temp)
	{
		str = *temp;
		if (str)
			ft_map_delete(env, str);
		temp++;
	}
	return (0);
}
