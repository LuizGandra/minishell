/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:17:56 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/30 12:53:18 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "parser.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>

# define MINISHELL "\033[36mminishell: \033[0m"

// =========================== EXTERN FUNCTIONS ===============================

typedef struct s_token_list	t_token_list;
typedef struct s_exec_tree	t_exec_tree;

extern t_token_list			*get_token_list(char *input);
void						clone_terminal(void);
void						reset_terminal(void);

// =========================== ================ ===============================

// The main structure of the shell
typedef struct s_shell
{
	t_hash_table			*env;
	t_exec_tree				*tree;
	char					*user_input;
	t_token_list			*tokens;
	int						default_fds[2];
	t_bool					exit;
	struct termios			termios;
}							t_shell;

// ============================== GLOBAL ======================================

t_shell						*get_minishell(void);

// ============================== UTILS =======================================

int							clean_all(void);
char						*ft_getpid(void);
char						*ft_readline(void);

// ============================== ENV FUNCTIONS ===============================

void						init_env(void);
char						*ft_getenv(char *key);
t_int8						ft_setenv(char *key, char *value, t_bool free_val);
t_hash_table				*env_to_map(char **env);
char						**map_to_env(t_hash_table *map);

#endif