/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/02 12:04:28 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexing.h"
#include "minishell.h"
#include "signals.h"

int					g_received_signal;

static void			ft_loop(void);

// static char	*get_type(t_token token)
// {
// 	if (token.type == TOK_PIPE)
// 		return ("TOK_PIPE");
// 	else if (token.type == WORD)
// 		return ("WORD");
// 	else if (token.type == TOK_REDIR_IN)
// 		return ("TOK_REDIR_IN");
// 	else if (token.type == TOK_REDIR_OUT)
// 		return ("TOK_REDIR_OUT");
// 	return ("UNKNOWN");
// }

// static void	print_tokens(t_token_list *tokens)
// {
// 	t_token_list	*tmp;

// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		ft_printf(C_CYA "type: " C_RST "%s" C_RED " value: " C_RST "%s\n",
// 			get_type(tmp->token), tmp->token.full_content);
// 		tmp = tmp->next;
// 	}
// }

// typedef struct s_exec_tree
// {
// 	t_tree_type			type;
// 	t_token_list		*command;
// 	struct s_exec_tree	*subshell;
// 	struct s_exec_tree	*left;
// 	struct s_exec_tree	*right;
// }						t_exec_tree;

static t_exec_tree	*build_test_tree(void)
{
	t_exec_tree	*root;

	// ls | cat -e > file || echo "error" && echo "success"
	root = ft_calloc(1, sizeof(t_exec_tree));
	root->type = TREE_AND;
	root->left = ft_calloc(1, sizeof(t_exec_tree));
	root->left->type = TREE_OR;
	root->left->left = ft_calloc(1, sizeof(t_exec_tree));
	root->left->left->type = TREE_PIPE;
	root->left->left->left = ft_calloc(1, sizeof(t_exec_tree));
	root->left->left->left->type = TREE_COMMAND;
	root->left->left->left->command = get_token_list("ls");
	root->right = ft_calloc(1, sizeof(t_exec_tree));
	root->right->type = TREE_COMMAND;
	root->right->command = get_token_list("echo \"success\"");
	root->left->right = ft_calloc(1, sizeof(t_exec_tree));
	root->left->right->type = TREE_COMMAND;
	root->left->right->command = get_token_list("echo \"error\"");
	root->left->left->right = ft_calloc(1, sizeof(t_exec_tree));
	root->left->left->right->type = TREE_REDIR_OUT;
	root->left->left->right->file = "file";
	root->left->left->right->left = ft_calloc(1, sizeof(t_exec_tree));
	root->left->left->right->left->type = TREE_COMMAND;
	root->left->left->right->left->command = get_token_list("cat -e");
	return (root);
}

int	main(void)
{
	init_env();
	ft_loop();
	return (clean_all());
}
static void clone_terminal(void)
{
	t_shell	*shell;

	shell = get_minishell();
	tcgetattr(STDIN_FILENO, &shell->termios);
	// REDUP FDS
}

static void reset_terminal(void)
{
	t_shell	*shell;

	shell = get_minishell();
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios);
	// REDUP FDS
}

static void	ft_loop(void)
{
	t_shell	*shell;

	listen_signals();
	clone_terminal();
	shell = get_minishell();
	while (!shell->exit)
	{
		g_received_signal = 0;
		reset_terminal();
		ft_printf("ls | cat -e > file || echo \"error\" && echo \"success\"\n");
		shell->user_input = ft_readline();
		if (!shell->user_input)
		{
			ft_printf("exit\n");
			break ;
		}
		if (shell->user_input[0] == '\0')
			continue ;
		add_history(shell->user_input);
		// shell->tokens = get_token_list(shell->user_input);
		exec(build_test_tree());
		// print_tokens(shell->tokens);
		ft_gc_exit();
	}
}
