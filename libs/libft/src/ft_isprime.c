/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:30:10 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/03/07 10:00:16 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isprime(unsigned long n)
{
	unsigned long	i;

	if (n < 2)
		return (FALSE);
	if (n == 2 || n == 3)
		return (TRUE);
	if (n % 2 == 0 || n % 3 == 0)
		return (FALSE);
	i = 5;
	while (i * i <= n)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return (FALSE);
		i += 6;
	}
	return (TRUE);
}
