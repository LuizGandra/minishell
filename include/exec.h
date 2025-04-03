/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:55 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/03 14:25:51 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"
# include <sys/wait.h>

# define O_C O_CREAT
# define O_T O_TRUNC
# define O_W O_WRONLY
# define O_R O_RDONLY
# define O_A O_APPEND

typedef enum e_pipe_fd
{
	READ_FD = 0,
	WRITE_FD = 1,
}	t_pipe_fd;

int	exec(t_exec_tree *tree, int fds[2]);

#endif