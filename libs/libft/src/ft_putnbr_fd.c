/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:33:32 by lhenriqu          #+#    #+#             */
/*   Updated: 2024/10/14 20:55:00 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		divisor;
	long	nlong;
	char	c;

	nlong = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nlong = -nlong;
	}
	divisor = 1;
	while (nlong / divisor >= 10)
		divisor *= 10;
	while (divisor)
	{
		c = (nlong / divisor) + '0';
		write(fd, &c, 1);
		nlong %= divisor;
		divisor /= 10;
	}
}
