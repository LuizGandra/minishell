/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:31:00 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/11 10:14:13 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GC_H
# define FT_GC_H

# include "../../libft.h"
# include "../../ft_bool.h"

// Main structure for the garbage collector
typedef struct s_ctx
{
	void			*ptr;
	struct s_ctx	*next;
}					t_ctx;

// Malloc and put the pointer in the garbage collector to manage it
void				*ft_gc_malloc(size_t size);
// Free the pointer and remove it from the garbage collector
void				ft_gc_free(void *ptr);
// Free all the pointers in the garbage collector
void				ft_gc_exit(void);
// Add a pointer to the garbage collector
t_bool				ft_gc_add(void *ptr);

#endif