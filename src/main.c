/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/17 15:04:44 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "minishell.h"

static void	ft_loop(void);

int	main(void)
{
	init_env();
	ft_loop();
	handle_error(E_SUCCESS);
}

static char	*get_token_type(t_token_type type)
{
    if (type == PIPE)
        return ("PIPE");
    else if (type == SEMICOLON)
        return ("SEMICOLON");
    else if (type == WORD)
        return ("WORD");
    else if (type == REDIR_IN)
        return ("REDIRECT_IN");
    else if (type == REDIR_OUT)
        return ("REDIRECT_OUT");
    else if (type == REDIR_OUT_APP)
        return ("REDIRECT_APPEND");
    else if (type == REDIR_HDOC)
        return ("REDIRECT_HEREDOC");
    else if (type == OPEN_BRACKET)
		return ("OPEN_BRACKET");
	else if (type == CLOSE_BRACKET)
		return ("CLOSE_BRACKET");
	else if (type == AND)
		return ("AND");
	else if (type == OR)
		return ("OR");
	else
		return ("UNKNOWN");
}

static void	print_tokens(t_token_list *tokens)
{
	t_token_list	*tmp;

	tmp = tokens;
	while (tmp)
	{
		ft_printf(C_GRN C_BLD "Token:" C_RST "%s, " C_CYA "type:" C_YEL " %s\n" C_RST, tmp->token.content,
			get_token_type(tmp->token.type));
		tmp = tmp->next;
	}
}

static void	ft_loop(void)
{
	t_shell *shell;

	shell = get_minishell();
	while (TRUE)
	{
		shell->user_input = readline(C_CYA "minishell$> " C_RST);
		if (!shell->user_input)
		{
			ft_printf("exit\n");
			break ;
		}
		add_history(shell->user_input);
		shell->tokens = get_token_list(shell->user_input);
		print_tokens(shell->tokens);
	}
}