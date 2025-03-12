/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 09:12:39 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/11 09:34:26 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;
	size_t	cpy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == old_size)
		return (ptr);
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size < old_size)
		cpy_size = new_size;
	else
		cpy_size = old_size;
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, cpy_size);
	free(ptr);
	return (new_ptr);
}
