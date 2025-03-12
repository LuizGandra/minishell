/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:35:55 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/17 16:11:37 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

// MACROS
# define DECIMAL_BASE "0123456789"
# define HEXA_UP "0123456789ABCDEF"
# define HEXA_LOW "0123456789abcdef"

// Print a string with specified format
int		ft_printf(const char *format, ...);
size_t	ft_putchar(char c);
size_t	ft_putstr(char *str);
size_t	ft_putptr(unsigned long number, char *base);
size_t	ft_putnbr_base(long int number, char *base);

// Print a string with specified format to a file descriptor
int		ft_printf_fd(int fd, const char *format, ...);

#endif
