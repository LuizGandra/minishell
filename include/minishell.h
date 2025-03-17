/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:17:56 by lcosta-g          #+#    #+#             */
/*   Updated: 2025/03/17 13:18:53 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_token_list	t_token_list;
t_token_list			*get_token_list(char *input);

typedef enum e_error
{
	E_SUCCESS,
	E_MALLOC_FAILED,
	E_INVALID_TOKEN,
}							t_error;

typedef struct s_shell
{
	t_hash_table			*table;
	char					*user_input;
	t_token_list			*tokens;
}							t_shell;

t_shell						*get_minishell(void);
void						init_env(void);
void						handle_error(t_error error);

#endif