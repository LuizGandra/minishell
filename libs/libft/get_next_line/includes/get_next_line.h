/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:30:48 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/17 16:16:13 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../../libft.h"

# include <stdlib.h>
# include <unistd.h>

// get the next line from specified file descriptor
char	*get_next_line(int fd);
char	*get_nl_address(const char *s);
char	*ft_strjoin_with_free(char *s1, char *s2);

// Returns the static buffer of GNL
char	**get_gnl_buffer(void);

// Closes the file descriptor and clears its associated static buffer
void	close_and_clear(int fd);

#endif
