/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:29:56 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/03 08:30:18 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpid(void)
{
	int		fd;
	char	*pid;
	char	*line;

	fd = open("/proc/self/stat", O_RDONLY);
	line = get_next_line(fd);
	pid = ft_substr(line, 0, ft_strchr(line, ' ') - line);
	free(line);
	close_and_clear(fd);
	return (pid);
}
