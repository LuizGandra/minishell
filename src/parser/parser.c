/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:07:30 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/28 12:12:43 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "parser.h"

static t_token_list	*get_priority_token(t_token_list *token_list,
						t_tree_hierarchy hierarchy);
static t_exec_tree	*handle_redirect(t_exec_tree *tree, t_token_list *list);
t_tree_type			get_tree_type(t_token_type token_type);

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
	tree->type = get_tree_type(priority->token.type);
	if (priority->token.type == TOK_WORD)
		tree->command = ft_sublist(token_list, token_list, NULL);
	else if (is_bracket(priority->token))
		tree->subshell = get_token_tree(ft_sublist(token_list, token_list->next,
					ft_lstlast(token_list)), ROOT);
	else if (is_redirector(priority->token))
		tree->left = handle_redirect(tree, token_list);
	else
	{
		tree->left = get_token_tree(ft_sublist(token_list, token_list,
					priority), LEFT_CHILD);
		tree->right = get_token_tree(ft_sublist(token_list, priority->next,
					NULL), RIGHT_CHILD);
	}
	return (tree);
}

// ! "> b ↔️ ls ↔️ -a ↔️ < a"
// TODO create a function to put the priority token in the left child
// TODO recursively, until all redirects are finished
// TODO remove the priority redirect from the list
static t_exec_tree	*handle_redirect(t_exec_tree *tree, t_token_list *list)
{
	t_token_list	*new_list;
	t_token_list	*temp;
	t_token_list	*prev;
	t_token_list	*new_priority;

	prev = NULL;
	new_list = ft_sublist(list, list, NULL);
	if (!new_list)
		return (NULL);
	temp = new_list;
	while (temp)
	{
		if (is_redirector(temp->token))
		{
			new_priority = temp;
			if (prev)
				prev->next = temp->next;
			if (temp->next)
				temp->next->prev = prev;
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	if (tree->type == TREE_REDIR_HDOC)
		tree->here_doc_fd = here_doc(new_priority->token.file->full_content);
	else
		tree->file = new_priority;
	return (get_token_tree(new_list, LEFT_CHILD));
}

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
	if (is_subshell(token_list))
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
