/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:55 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/08 13:43:35 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parser.h"

# include <sys/wait.h>

# define MINISHELL "\033[36mminishell: \033[0m"
# define IS_A_DIR "\033[31mIs a directory\n\033[0m"
# define CMD_NFOUND "\033[31mcommand not found\n\033[0m"
# define PERM_DENIED "\033[31mPermission denied\n\033[0m"
# define AMBIG_REDIR "\033[31mambiguous redirect\n\033[0m"
# define FILE_NFOUND "\033[31mNo such file or directory\n\033[0m"

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

// Iterate through the execution tree recursively and execute each node
int		exec(t_exec_tree *tree, int fds[2]);

// ================================= RUN FUNCTIONS ============================

int		run_builtin(t_token_list *command);
void	run_external(t_token_list *command);

// ================================= UTILS ====================================

char	*handle_path(char *cmd);
char	**handle_argv(t_token_list *list);
t_bool	is_builtin(t_token_list *command);

// ================================= MACROS ===================================

// Return the exit code of a process
int		wexitstatus(int status);
// Return true if the process was killed by a signal
int		wifsignaled(int status);
// Return the signal number that killed the process
int		wtermsig(int status);
// Return true if the process dumped core
int		wcoredump(int status);
// Calculate the exit code of a process
int		get_return_value(int status);

// ================================= BUILTINS =================================

typedef	int(t_builtin)(char **args);

int		b_echo(char **args);
int		b_pwd(char **args);
int		b_exit(char **args);

#endif