/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:26:05 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/25 15:27:46 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_bool	is_varchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}
static char	*handle_var(char *str, char **output)
{
	size_t	len;
	char	*key;

	str++;
	len = 0;
	while (is_varchar(str[len]))
		len++;
	key = ft_substr(str, 0, len);
	*output = ft_strjoin_with_free(*output, get_env(key));
	free(key);
	return (str + len);
}

void	expand_vars(t_content_part *part)
{
	char	*output;
	char	*tmp;
	char	*str;
	size_t	len;

	output = ft_strdup("");
	str = part->str;
	while (*str)
	{
		len = 0;
		while (str[len] && str[len] != '$')
			len++;
		tmp = ft_substr(str, 0, len);
		output = ft_strjoin_with_free(output, tmp);
		free(tmp);
		str += len;
		str = handle_var(str, &output);
	}
	free(part->str);
	part->str = output;
}
