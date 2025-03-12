/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:12:52 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/17 16:13:51 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_nl_address(const char *s)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	return (NULL);
}

void	close_and_clear(int fd)
{
	char	**buffer;

	buffer = get_gnl_buffer();
	if (fd >= 0 && fd < 1024)
	{
		if (buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		close(fd);
	}
}

char	**get_gnl_buffer(void)
{
	static char	*buffer[1024];

	return ((char **)buffer);
}

char	*ft_strjoin_with_free(char *s1, char *s2)
{
	char	*new_string;
	int		j;
	int		i;

	if (s1 == NULL)
		s1 = ft_strdup("");
	new_string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		new_string[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new_string[j++] = s2[i++];
	new_string[j] = '\0';
	free((char *)s1);
	return (new_string);
}
