/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:33:22 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/14 10:37:12 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_hex(unsigned long long n, char *base)
{
	if (n < 16)
		ft_putchar(base[n]);
	else if (n >= 16)
	{
		ft_put_hex(n / 16, base);
		ft_put_hex(n % 16, base);
	}
	else
		ft_putchar(n + 48);
}

int	ft_print_hex(unsigned long long n, char format)
{
	char	*base_lower;
	char	*base_upper;
	int		len;

	base_lower = "0123456789abcdef";
	base_upper = "0123456789ABCDEF";
	len = 0;
	if (n == 0)
		len += write(1, "0", 1);
	else
	{
		if (format == 'x')
			ft_put_hex(n, base_lower);
		if (format == 'X')
			ft_put_hex(n, base_upper);
	}
	while (n)
	{
		n /= 16;
		++len;
	}
	return (len);
}

int	ft_print_ptr(unsigned long long n)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	len += ft_print_hex(n, 'x');
	return (len);
}