/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:32:00 by gkrusta           #+#    #+#             */
/*   Updated: 2023/08/28 14:55:56 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_helper(const char *s, int i)
{
	double	fraction;
	double	number;
	int		decimal_seen;

	fraction = 1.0;
	number = 0;
	decimal_seen = 0;
	while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
	{
		if (s[i] == '.')
		{
			decimal_seen = 1;
			i++;
		}
		if (!decimal_seen)
			number = (s[i] - '0') + (number * 10);
		else
		{
			fraction /= 10.0;
			number += (s[i] - '0') * fraction;
		}
		i++;
	}
	return (number);
}

double	ft_atof(const char *s)
{
	int		i;
	int		sign;
	double	number;

	i = 0;
	sign = 1;
	number = 0.0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if ((s[i] == '+' || s[i] == '-') && (s[i + 1] >= '0' && s[i + 1] <= '9'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	number = ft_helper(&s[i], i);
	return (sign * number);
}

/* int	main(void)
{
	char	*s;

	s = "          -0.34123*abc1234";
	printf("%f\n", ft_atof(s));
	printf("%f\n", atof(s));
} */