/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:40:14 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/19 08:16:37 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gc.h"

static t_ctx	*get_global_ctx(void)
{
	static t_ctx	g_ctx;

	return (&g_ctx);
}

void	*ft_gc_malloc(size_t size)
{
	t_ctx	*ctx;
	void	*ptr;

	ctx = get_global_ctx();
	ptr = ft_calloc(1, size);
	if (!ptr)
		return (NULL);
	ctx->ptr = ptr;
	ctx->next = ft_calloc(1, sizeof(t_ctx));
	if (!ctx->next)
	{
		free(ptr);
		ctx->ptr = NULL;
		return (NULL);
	}
	return (ptr);
}

void	ft_gc_free(void *ptr)
{
	t_ctx	*ctx;
	t_ctx	*tmp;

	ctx = get_global_ctx();
	while (ctx->next)
	{
		if (ctx->ptr == ptr)
		{
			free(ctx->ptr);
			tmp = ctx->next;
			ctx->ptr = tmp->ptr;
			ctx->next = tmp->next;
			free(tmp);
			return ;
		}
		ctx = ctx->next;
	}
}

void	ft_gc_exit(void)
{
	t_ctx	*ctx;
	t_ctx	*tmp;

	ctx = get_global_ctx();
	while (ctx->next)
	{
		free(ctx->ptr);
		tmp = ctx->next;
		ctx->ptr = tmp->ptr;
		ctx->next = tmp->next;
		free(tmp);
	}
	get_global_ctx()->ptr = NULL;
	get_global_ctx()->next = NULL;
}

t_bool	ft_gc_add(void *ptr)
{
	t_ctx	*ctx;

	ctx = get_global_ctx();
	while (ctx->next)
	{
		if (ctx->ptr == ptr)
			return (TRUE);
		ctx = ctx->next;
	}
	ctx->next = ft_calloc(1, sizeof(t_ctx));
	if (!ctx->next)
		return (FALSE);
	ctx->ptr = ptr;
	return (TRUE);
}
