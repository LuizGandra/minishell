/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:15:36 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 15:22:54 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lexing.h"
#include "minishell.h"
#include "signals.h"

int					g_received_signal;

static void			ft_loop(void);

// sleep 500
static t_exec_tree	*build_sleep_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_COMMAND;
    root->command = get_token_list("sleep 500");

    return (root);
}

// python3
static t_exec_tree	*build_python3_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_COMMAND;
    root->command = get_token_list("python3");

    return (root);
}

// (echo "hello") > output.txt
static t_exec_tree	*build_redir_subshell_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_REDIR_OUT;
    root->file = "output.txt";

    root->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->type = TREE_SUBSHELL;
    root->left->subshell = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->subshell->type = TREE_COMMAND;
    root->left->subshell->command = get_token_list("echo \"hello\"");

    return (root);
}

// mkdir test || echo "failed" && echo "success"
static t_exec_tree	*build_and_or_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_AND;

    root->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->type = TREE_OR;
    root->left->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->left->type = TREE_COMMAND;
    root->left->left->command = get_token_list("mkdir test");
    root->left->right = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->right->type = TREE_COMMAND;
    root->left->right->command = get_token_list("echo \"failed\"");

    root->right = ft_gc_malloc(sizeof(t_exec_tree));
    root->right->type = TREE_COMMAND;
    root->right->command = get_token_list("echo \"success\"");

    return (root);
}

// ls | grep txt | wc -l
static t_exec_tree	*build_multi_pipe_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_PIPE;

    root->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->type = TREE_PIPE;
    root->left->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->left->type = TREE_COMMAND;
    root->left->left->command = get_token_list("ls");
    root->left->right = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->right->type = TREE_COMMAND;
    root->left->right->command = get_token_list("grep txt");

    root->right = ft_gc_malloc(sizeof(t_exec_tree));
    root->right->type = TREE_COMMAND;
    root->right->command = get_token_list("wc -l");

    return (root);
}

// echo "hello" >> output.txt
static t_exec_tree	*build_redir_append_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_REDIR_APPEND;
    root->file = "output.txt";

    root->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->type = TREE_COMMAND;
    root->left->command = get_token_list("echo \"hello\"");

    return (root);
}

// cat < input.txt
static t_exec_tree	*build_redir_in_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_REDIR_IN;
    root->file = "input.txt";

    root->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->type = TREE_COMMAND;
    root->left->command = get_token_list("cat");

    return (root);
}

// (ls -l | grep txt) && echo "done"
static t_exec_tree	*build_subshell_tree(void)
{
    t_exec_tree	*root;

    root = ft_gc_malloc(sizeof(t_exec_tree));
    root->type = TREE_AND;

    root->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->type = TREE_SUBSHELL;
    root->left->subshell = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->subshell->type = TREE_PIPE;
    root->left->subshell->left = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->subshell->left->type = TREE_COMMAND;
    root->left->subshell->left->command = get_token_list("ls -l");
    root->left->subshell->right = ft_gc_malloc(sizeof(t_exec_tree));
    root->left->subshell->right->type = TREE_COMMAND;
    root->left->subshell->right->command = get_token_list("grep txt");

    root->right = ft_gc_malloc(sizeof(t_exec_tree));
    root->right->type = TREE_COMMAND;
    root->right->command = get_token_list("echo \"done\"");

    return (root);
}

// ls | grep m |cat -e > file || echo "error" && echo "success"
static t_exec_tree	*build_test_tree(void)
{
	t_exec_tree	*root;

	root = ft_gc_malloc(sizeof(t_exec_tree));
	root->type = TREE_AND;
	root->left = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->type = TREE_OR;
	root->left->left = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->left->type = TREE_PIPE;
	root->left->left->left = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->left->left->type = TREE_PIPE;
	root->left->left->left->left = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->left->left->left->type = TREE_COMMAND;
	root->left->left->left->left->command = get_token_list("ls");
	root->left->left->left->right = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->left->left->right->type = TREE_COMMAND;
	root->left->left->left->right->command = get_token_list("grep m");
	root->right = ft_gc_malloc(sizeof(t_exec_tree));
	root->right->type = TREE_COMMAND;
	root->right->command = get_token_list("echo \"success\"");
	root->left->right = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->right->type = TREE_COMMAND;
	root->left->right->command = get_token_list("echo \"error\"");
	root->left->left->right = ft_gc_malloc(sizeof(t_exec_tree));
	root->left->left->right->type = TREE_REDIR_OUT;
	root->left->left->right->file = "file";
	root->left->left->right->left = ft_gc_malloc(sizeof(t_exec_tree));
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
static void	clone_terminal(void)
{
	t_shell	*shell;

	shell = get_minishell();
	tcgetattr(STDIN_FILENO, &shell->termios);
	shell->default_fds[READ_FD] = dup(STDIN_FILENO);
	shell->default_fds[WRITE_FD] = dup(STDOUT_FILENO);
}

static void	reset_terminal(void)
{
	t_shell	*shell;

	shell = get_minishell();
	tcsetattr(STDIN_FILENO, TCSANOW, &shell->termios);
	dup2(shell->default_fds[READ_FD], STDIN_FILENO);
	dup2(shell->default_fds[WRITE_FD], STDOUT_FILENO);
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
		exec(build_python3_tree(), shell->default_fds);
		// print_tokens(shell->tokens);
		ft_gc_exit();
	}
}
