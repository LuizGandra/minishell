/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:17:56 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/03/31 17:12:22 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_token_list	t_token_list;
t_token_list				*get_token_list(char *input);

typedef enum e_error
{
	E_SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_TOKEN,
}							t_error;

typedef struct s_shell
{
	t_hash_table			*env;
	char					*user_input;
	t_token_list			*tokens;
	t_bool					exit;
}							t_shell;

t_shell						*get_minishell(void);
void						init_env(void);
char						*ft_getenv(char *key);
void						handle_error(t_error error);

#endif