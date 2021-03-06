/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 22:31:33 by oel-bour          #+#    #+#             */
/*   Updated: 2019/10/10 22:31:35 by oel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putstr_fd(char *s, int fd)
{
	int			l;
	const char	*h;

	if (s != NULL)
	{
		h = (const char*)s;
		l = ft_strlen(h);
		write(fd, s, l);
	}
}
