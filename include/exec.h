/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:55 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 15:30:37 by lhenriqu         ###   ########.fr       */
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
}		t_pipe_fd;

char	**handle_argv(t_token_list *list);
t_bool	is_builtin(t_token_list *command);
int		exec(t_exec_tree *tree, int fds[2]);
void	run_external(t_token_list *command);
char	*handle_path(char *cmd);
int		run_builtin(t_token_list *command);

// ================================= MACROS ===================================

// Calculate the exit code of a process
int		get_return_value(int status);
// Return the exit code of a process
int		wexitstatus(int status);
// Return true if the process was killed by a signal
int		wifsignaled(int status);
// Return the signal number that killed the process
int		wtermsig(int status);
// Return true if the process dumped core
int		wcoredump(int status);

// ================================= BUILTINS =================================

typedef	int(t_builtin)(char **args);

int		b_echo(char **args);
int		b_pwd(char **args);
int		b_exit(char **args);

#endif