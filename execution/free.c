/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bour <oel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:24:32 by oel-bour          #+#    #+#             */
/*   Updated: 2020/03/09 10:40:05 by oel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_free(char **arg)
{
	if (arg && *arg)
		free(*arg);
	*arg = NULL;
	return (1);
}

int		ft_free_star_ok(char **arg)
{
	int i;

	if (arg == NULL)
		return (0);
	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	return (0);
}

int		ft_free_star(char **arg)
{
	int i;

	if (arg == NULL)
		return (0);
	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
	arg = NULL;
	return (0);
}

void	ft_free_void(void **arg)
{
	if (arg && *arg)
		free(*arg);
	*arg = NULL;
}

void	ft_free_void_star(void **arg)
{
	int i;

	if (arg == NULL)
		return ;
	i = 0;
	while (arg[i])
	{
		ft_free_void(&arg[i]);
		i++;
	}
}
