/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:36:00 by lhenriqu          #+#    #+#             */
/*   Updated: 2024/12/30 12:56:49 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_putptr(unsigned long number, char *base)
{
	size_t	len;
	int		base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number == 0)
		return (ft_putstr("(nil)"));
	if (number >= (unsigned long)base_len)
		len += ft_putptr((number / base_len), base);
	else
		len += ft_putstr("0x");
	len += ft_putchar(base[number % base_len]);
	return (len);
}

size_t	ft_putnbr_base(long int number, char *base)
{
	size_t	len;
	int		base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number == -2147483648)
	{
		len += ft_putchar('-');
		len += ft_putchar('2');
		number = 147483648;
	}
	if (number < 0)
	{
		len += ft_putchar('-');
		number *= -1;
	}
	if (number >= base_len)
		len += ft_putnbr_base((number / base_len), base);
	len += ft_putchar(base[number % base_len]);
	return (len);
}
