/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:03:51 by lhenriqu          #+#    #+#             */
/*   Updated: 2024/11/29 11:03:51 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_validate(char c, int base);

int	ft_atoi_base(const char *str, int str_base)
{
	int	index;
	int	result;
	int	signal;

	index = 0;
	result = 0;
	signal = 1;
	while ((str[index] == ' ') || ((str[index] >= 9) && (str[index] <= 13)))
		index++;
	if ((str[index] == '-') || (str[index] == '+'))
	{
		if (str[index] == '-')
			signal *= -1;
		index++;
	}
	while ((ft_validate(str[index], str_base)) != -1)
	{
		result *= str_base;
		result += ft_validate(str[index], str_base);
		index++;
	}
	return (result * signal);
}

static int	ft_validate(char c, int base)
{
	char	*low_base;
	char	*upper_base;
	int		index;

	low_base = "0123456789abcdef";
	upper_base = "0123456789ABCDEF";
	index = 0;
	while (index < base)
	{
		if ((low_base[index] == c) || (upper_base[index] == c))
			return (index);
		index++;
	}
	return (-1);
}
