/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:07:30 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/09 14:18:46 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parser.h"

static t_token_list	*get_priority_token(t_token_list *token_list,
						t_tree_hierarchy hierarchy);
static void			handle_redirect(t_exec_tree *tree, t_token_list *priority,
						t_tree_hierarchy hierarchy);

// TODO
// ? check this question -> I need to copy the token list or
// ? the priority token before add this to the tree, probably using ft_sublist

t_exec_tree	*get_token_tree(t_token_list *token_list,
		t_tree_hierarchy hierarchy)
{
	t_token_list	*priority;
	t_exec_tree		*tree;

	if (!token_list)
		return (NULL);
	tree = ft_gc_malloc(sizeof(t_exec_tree));
	if (!tree)
		return (NULL);
	priority = get_priority_token(token_list, hierarchy);
	tree->type = priority->token.type;
	if (tree->type == TOK_WORD)
		tree->command = ft_sublist(token_list, token_list, NULL);
	else if (is_bracket(priority->token))
		tree->subshell = get_token_tree(ft_sublist(token_list, token_list->next,
					ft_lstlast(token_list)->prev), ROOT);
	else if (is_redirector(priority->token))
		handle_redirect(tree, priority, hierarchy);
	else
	{
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

static t_token_list	*get_priority_token(t_token_list *token_list,
		t_tree_hierarchy hierarchy)
{
	t_token_list	*priority;
	t_token_list	*list;

	if (hierarchy == ROOT || hierarchy == LEFT_CHILD)
		list = ft_lstlast(token_list);
	else
		list = token_list;
	if (is_a_subshell(list))
		return (list);
	while (list)
	{
		if (list->token.type == TOK_OPEN_BRACKET
			|| list->token.type == TOK_CLOSE_BRACKET)
			pass_brackets(&list, hierarchy);
		if (list->token.type == TOK_OR || list->token.type == TOK_AND)
			return (list);
		if (!priority || compare_priority(list->token.type,
				priority->token.type) == 1)
			priority = list;
		list = get_next_token(list, hierarchy);
	}
	return (priority);
}
