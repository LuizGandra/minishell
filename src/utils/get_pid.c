/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:29:56 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/18 17:26:20 by lcosta-g         ###   ########.fr       */
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
