/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 07:44:19 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/01 13:21:48 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec(t_exec_tree *tree)
{
	int	result;

	if (tree->type == SUBSHELL)
		return (exec(tree->subshell));
	result = exec(tree->left);
	if (tree->type == OR && result)
		result = exec(tree->right);
	else if (tree->type == AND && !result)
		result = exec(tree->right);
		
	// EXECUTION
	
	return (result);
}
