/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_prime.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:10:33 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/07 11:00:54 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_next_prime(unsigned long x)
{
	if (x < 2)
		return (2);
	if (x % 2 == 0)
		x++;
	while (!ft_isprime(x))
		x += 2;
	return (x);
}
