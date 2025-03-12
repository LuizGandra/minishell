/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:51:58 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/17 16:15:41 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

size_t	ft_putchar_fd(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

size_t	ft_putstr_fd(int fd, char *str)
{
	int	len;

	if (str == NULL)
		return (ft_putstr_fd(fd, "(null)"));
	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
	return (len);
}

size_t	ft_putptr_fd(int fd, unsigned long number, char *base)
{
	size_t	len;
	int		base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number == 0)
		return (ft_putstr_fd(fd, "(nil)"));
	if (number >= (unsigned long)base_len)
		len += ft_putptr_fd(fd, (number / base_len), base);
	else
		len += ft_putstr_fd(fd, "0x");
	len += ft_putchar_fd(fd, base[number % base_len]);
	return (len);
}

size_t	ft_putnbr_base_fd(int fd, long int number, char *base)
{
	size_t	len;
	int		base_len;

	len = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (number == -2147483648)
	{
		len += ft_putchar_fd(fd, '-');
		len += ft_putchar_fd(fd, '2');
		number = 147483648;
	}
	if (number < 0)
	{
		len += ft_putchar_fd(fd, '-');
		number *= -1;
	}
	if (number >= base_len)
		len += ft_putnbr_base_fd(fd, (number / base_len), base);
	len += ft_putchar_fd(fd, base[number % base_len]);
	return (len);
}
