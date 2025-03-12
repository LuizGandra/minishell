/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:39:40 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/03 15:44:53 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void **matrix, void (*free_func)(void *))
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free_func(matrix[i]);
		i++;
	}
	free(matrix);
}
