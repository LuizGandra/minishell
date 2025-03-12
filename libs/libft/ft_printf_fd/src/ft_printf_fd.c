/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:43:12 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/17 16:16:27 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"

static size_t	ft_check_format_fd(int fd, char c, va_list args);

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	size_t	len;
	size_t	i;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += ft_check_format_fd(fd, format[i], args);
		}
		else
			len += ft_putchar_fd(fd, format[i]);
		i++;
	}
	va_end(args);
	return ((int)len);
}

static size_t	ft_check_format_fd(int fd, char c, va_list args)
{
	size_t	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar_fd(fd, (char)va_arg(args, int));
	else if (c == 's')
		count += ft_putstr_fd(fd, va_arg(args, char *));
	else if (c == 'p')
		count += ft_putptr_fd(fd, va_arg(args, unsigned long), HEXA_LOW);
	else if (c == 'd' || c == 'i')
		count += ft_putnbr_base_fd(fd, va_arg(args, int), DECI_BASE);
	else if (c == 'u')
		count += ft_putnbr_base_fd(fd, va_arg(args, unsigned int), DECI_BASE);
	else if (c == 'x')
		count += ft_putnbr_base_fd(fd, va_arg(args, unsigned int), HEXA_LOW);
	else if (c == 'X')
		count += ft_putnbr_base_fd(fd, va_arg(args, unsigned int), HEXA_UP);
	else if (c == '%')
		count += ft_putchar_fd(fd, '%');
	return (count);
}
