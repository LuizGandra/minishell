/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 20:10:09 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/09 12:20:49 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_negative(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static size_t	count_char(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nlong;
	size_t	digits;
	int		negative;
	char	*str;

	negative = is_negative(n);
	nlong = (long)n;
	if (negative == 1)
		nlong = -nlong;
	digits = count_char(nlong);
	str = (char *)malloc(negative + digits + 1);
	if (str == NULL)
		return (NULL);
	if (negative == 1)
		str[0] = '-';
	str[digits + negative] = '\0';
	while (digits > 0)
	{
		str[(digits - 1) + negative] = (nlong % 10) + '0';
		nlong /= 10;
		digits--;
	}
	return (str);
}
