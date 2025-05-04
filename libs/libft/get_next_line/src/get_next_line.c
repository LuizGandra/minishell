/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:28:40 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/05/02 21:43:58 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *buffer);
static char	*get_line(char *buffer);
static char	*get_rest(char *buffer);

char	*get_next_line(int fd)
{
	char	**buffer;
	char	*line;

	buffer = get_gnl_buffer();
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	line = NULL;
	line = get_line(buffer[fd]);
	buffer[fd] = get_rest(buffer[fd]);
	return (line);
}

static char	*ft_read(int fd, char *buffer)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!(get_nl_address(buffer)) && (bytes_read != 0))
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		buffer = ft_strjoin_with_free(buffer, temp_buffer);
	}
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	char	*nl_address;
	size_t	line_len;

	if (buffer[0] == '\0')
		return (NULL);
	nl_address = get_nl_address(buffer);
	if (nl_address)
		line_len = nl_address - buffer;
	else
	{
		line_len = 0;
		while (buffer[line_len])
			line_len++;
	}
	line = malloc((line_len + 2) * sizeof(char));
	if (line == NULL)
		return (NULL);
	line = ft_strncpy(line, buffer, line_len);
	if (nl_address)
		line[line_len++] = '\n';
	line[line_len] = '\0';
	return (line);
}

static char	*get_rest(char *buffer)
{
	char	*rest;
	char	*nl_address;

	rest = NULL;
	nl_address = get_nl_address(buffer);
	if (nl_address)
		rest = ft_strdup(nl_address + 1);
	free(buffer);
	return (rest);
}
