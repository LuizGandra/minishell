/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-g <lcosta-g@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:28:57 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/17 08:50:19 by lcosta-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	count_cmds(t_exec_tree *tree)
{
	size_t	count;

	count = 0;
	if (tree->type == TREE_CMD)
		return (1);
	if (tree->subshell)
		count += count_cmds(tree->subshell);
	if (tree->left)
		count += count_cmds(tree->left);
	if (tree->right)
		count += count_cmds(tree->right);
	return (count);
}

t_pid_list	*create_pid_list(t_exec_tree *tree)
{
	t_pid_list	*list;

	list = ft_calloc(1, sizeof(t_pid_list));
	list->pids = ft_calloc(count_cmds(tree), sizeof(pid_t));
	return (list);
}

void	add_pid(t_pid_list *list, pid_t pid)
{
	list->pids[list->len] = pid;
	list->len++;
}

int	wait_pids(t_pid_list *list)
{
	size_t	i;
	int		status;
	int		ret_code;

	i = 0;
	ret_code = 0;
	while (i < list->len)
	{
		waitpid(list->pids[i], &status, 0);
		ret_code = get_return_value(status);
		i++;
	}
	ft_bzero(list->pids, sizeof(pid_t) * list->len);
	list->len = 0;
	return (ret_code);
}

void	free_pid_list(t_pid_list *list)
{
	if (list)
	{
		if (list->pids)
			free(list->pids);
		free(list);
	}
}
