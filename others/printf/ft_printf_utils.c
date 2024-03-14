/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgomes <vgomes@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:41:14 by vgomes            #+#    #+#             */
/*   Updated: 2024/03/14 10:37:20 by vgomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int i)
{
	return (write(1, &i, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printnum(long i)
{
	int	count;

	count = 0;
	if (i < 0)
	{
		ft_putchar('-');
		return (ft_printnum(-i) + 1);
	}
	if (i >= 10)
		count += ft_printnum(i / 10);
	return (count + ft_putchar(i % 10 + '0'));
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}