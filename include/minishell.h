/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:17:56 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/04/04 15:35:46 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>

typedef struct s_token_list	t_token_list;

t_token_list				*get_token_list(char *input);

typedef struct s_shell
{
	t_hash_table			*env;
	char					*user_input;
	t_token_list			*tokens;
	int						default_fds[2];
	t_bool					exit;
	struct termios			termios;
}							t_shell;

t_shell						*get_minishell(void);
char						**map_to_env(t_hash_table *map);
t_hash_table				*env_to_map(char **env);
void						init_env(void);
char						*ft_getenv(char *key);
void						ft_setenv(char *key, char *value,
								t_bool free_value);
int							clean_all(void);
char						*ft_readline(void);
char						*ft_getpid(void);

#endif