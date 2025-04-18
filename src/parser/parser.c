/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:07:30 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/17 12:24:06 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parser.h"

static t_token_list	*get_priority_token(t_token_list *token_list,
						t_tree_hierarchy hierarchy);
static void			handle_redirect(t_exec_tree *tree, t_token_list *priority,
						t_tree_hierarchy hierarchy);
t_tree_type			get_tree_type(t_token_type token_type);

t_exec_tree	*get_token_tree(t_token_list *token_list,
		t_tree_hierarchy hierarchy)
{
	t_token_list	*priority;
	t_exec_tree		*tree;

	ft_printf("\nget token tree foi chamada! %s -> %s\n",
		token_list->token.full_content, ft_lstlast(token_list)->token.full_content);
	if (!token_list)
		return (NULL);
	tree = ft_gc_malloc(sizeof(t_exec_tree));
	if (!tree)
		return (NULL);
	priority = get_priority_token(token_list, hierarchy);
	ft_printf("\npriority token: (%s, %i)\n",
			priority->token.full_content, priority->token.type);
	tree->type = get_tree_type(priority->token.type);
	if (priority->token.type == TOK_WORD)
	{
		ft_printf("\nget_token_tree é word!\n");
		tree->command = ft_sublist(token_list, token_list, NULL);
	}
	else if (is_bracket(priority->token))
	{
		ft_printf("\nget_token_tree é subshell!\n");
		tree->subshell = get_token_tree(ft_sublist(token_list, token_list->next,
			ft_lstlast(token_list)->prev), ROOT);
	}
	else if (is_redirector(priority->token))
	{
		ft_printf("\nget_token_tree é redirect!\n");
		handle_redirect(tree, priority, hierarchy);
	}
	else
	{
		ft_printf("\nget_token_tree caiu no último else!\n");
		tree->left = get_token_tree(ft_sublist(token_list, token_list,
					priority), LEFT_CHILD);
		tree->right = get_token_tree(ft_sublist(token_list, priority->next,
					NULL), RIGHT_CHILD);
	}
	return (tree);
}

// TODO create a function to put the priority token in the left child
// TODO recursively,until all redirects are finished
static void	handle_redirect(t_exec_tree *tree, t_token_list *priority,
		t_tree_hierarchy hierarchy)
{
	(void)tree;
	(void)priority;
	(void)hierarchy;
	// * 1. add redirect in the left child
	// * 2. fill here_doc_fd attribute, if necessary
}

// TODO aparentemente ta mt errado? kkkkkkkkkkkk
static t_token_list	*get_priority_token(t_token_list *token_list,
		t_tree_hierarchy hierarchy)
{
	t_token_list	*priority;
	t_token_list	*list;

	priority = NULL;
	if (hierarchy == ROOT || hierarchy == LEFT_CHILD)
	list = ft_lstlast(token_list);
	else
	list = token_list;

	ft_printf("get_priority_token recebeu a lista: ");
	print_token_list(list);

	if (is_a_subshell(list))
		return (list);
	while (list)
	{
		if (list->token.type == TOK_OPEN_BRACKET
			|| list->token.type == TOK_CLOSE_BRACKET)
			pass_brackets(&list, hierarchy); // TODO probably wrong function
		if (list->token.type == TOK_OR || list->token.type == TOK_AND)
			return (list);
		if (!priority || compare_priority(list->token.type,
				priority->token.type) == 1)
		{
			ft_printf("Nova prioridade: ['%s', %i]\n",
				list->token.full_content, list->token.type);
			priority = list;
		}
		list = get_next_token(list, hierarchy);
	}
	return (priority);
}

t_tree_type	get_tree_type(t_token_type token_type)
{
	if (token_type == TOK_OR)
		return (TREE_OR);
	else if (token_type == TOK_AND)
		return (TREE_AND);
	else if (token_type == TOK_PIPE)
		return (TREE_PIPE);
	else if (token_type == TOK_REDIR_IN)
		return (TREE_REDIR_IN);
	else if (token_type == TOK_REDIR_OUT)
		return (TREE_REDIR_OUT);
	else if (token_type == TOK_REDIR_OUT_APP)
		return (TREE_REDIR_OUT_APP);
	else if (token_type == TOK_REDIR_HDOC)
		return (TREE_REDIR_HDOC);
	else if (token_type == TOK_OPEN_BRACKET || token_type == TOK_CLOSE_BRACKET)
		return (TREE_SUBSHELL);
	else
		return (TREE_CMD);
}
