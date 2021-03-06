/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_ex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:06:50 by oel-bour          #+#    #+#             */
/*   Updated: 2020/03/09 14:52:03 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	**get_semi(t_command *head, int *n)
{
	t_command	*counter;
	t_command	**tab;
	int			i;

	if (head == NULL)
		return (NULL);
	counter = head;
	tab = (t_command**)ft_calloc(4096, sizeof(t_command*));
	i = 1;
	if (head->what != SEMICOL)
		tab[0] = head;
	while (counter)
	{
		if (counter->what == SEMICOL)
		{
			if (counter->next != NULL && counter->next->what != SEMICOL)
			{
				tab[i] = counter->next;
				i++;
			}
		}
		counter = counter->next;
	}
	*n = i;
	return (tab);
}

t_command	**get_pipe(t_command *head, int *n)
{
	t_command	**tab;
	int			i;

	if (head == NULL)
		return (NULL);
	tab = NULL;
	tab = (t_command**)ft_calloc(4096, sizeof(t_command*));
	i = 1;
	tab[0] = head;
	while (head != NULL)
	{
		if (head->what == SEMICOL)
			break ;
		if (head->what == PIPE)
		{
			g_p = 1;
			tab[i] = head->next;
			i++;
		}
		head = head->next;
	}
	*n = i;
	return (tab);
}
