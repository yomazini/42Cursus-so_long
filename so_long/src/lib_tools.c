/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:14:18 by ymazini           #+#    #+#             */
/*   Updated: 2025/03/11 20:56:48 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)s1[i] -(unsigned char)s2[i]);
}

static int	int_len(long c)
{
	int	i;

	i = 0;
	if (c <= 0)
	{
		i++;
		c = -c;
	}
	while (c)
	{
		c /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	c;
	char	*str;
	int		len;

	c = n;
	len = int_len(c);
	str = (char *)malloc (len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (c == 0)
		str[0] = '0';
	if (c < 0)
	{
		str[0] = '-';
		c = -c ;
	}
	while (c)
	{
		str[len--] = (c % 10) + '0';
		c /= 10;
	}
	return (str);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;
	size_t	i;

	slen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (slen);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}
