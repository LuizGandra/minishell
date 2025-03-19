/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:12:52 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/06 12:39:50 by lhenriqu         ###   ########.fr       */
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
	if (fd >= 0 && fd < FD_MAX)
	{
		clear_gnl_buffer(fd);
		close(fd);
	}
}

void	clear_gnl_buffer(int fd)
{
	char	**buffer;
	int		i;

	buffer = get_gnl_buffer();
	if (fd >= 0 && fd < FD_MAX)
	{
		if (buffer[fd])
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
	}
	if (fd == CLEAR_ALL)
	{
		i = 0;
		while (i < FD_MAX)
		{
			if (buffer[i])
			{
				free(buffer[i]);
				buffer[i] = NULL;
			}
			i++;
		}
	}
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

char	**get_gnl_buffer(void)
{
	static char	*buffer[FD_MAX];

	return ((char **)buffer);
}
