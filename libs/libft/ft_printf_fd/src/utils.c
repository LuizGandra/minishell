/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:51:58 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/04/04 09:22:40 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

size_t	pft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

size_t	pft_putstr_fd(int fd, char *str)
{
	int	len;

	if (str == NULL)
		return (pft_putstr_fd(fd, "(null)"));
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
	return (len);
}

size_t	pft_putptr_fd(int fd, unsigned long number, char *base)
{
	size_t	len;
	int		base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number == 0)
		return (pft_putstr_fd(fd, "(nil)"));
	if (number >= (unsigned long)base_len)
		len += pft_putptr_fd(fd, (number / base_len), base);
	else
		len += pft_putstr_fd(fd, "0x");
	len += pft_putchar_fd(fd, base[number % base_len]);
	return (len);
}

size_t	pft_putnbr_base_fd(int fd, long int number, char *base)
{
	size_t	len;
	int		base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number == -2147483648)
	{
		len += pft_putchar_fd(fd, '-');
		len += pft_putchar_fd(fd, '2');
		number = 147483648;
	}
	if (number < 0)
	{
		len += pft_putchar_fd(fd, '-');
		number *= -1;
	}
	if (number >= base_len)
		len += pft_putnbr_base_fd(fd, (number / base_len), base);
	len += pft_putchar_fd(fd, base[number % base_len]);
	return (len);
}
