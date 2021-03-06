/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 22:35:46 by oel-bour          #+#    #+#             */
/*   Updated: 2020/03/09 14:40:32 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		help_convert2(t_command *counter)
{
	char	**arg;
	t_env	*node;

	if (counter->str != NULL && counter->str[0] != '=' &&
	ft_strrchr(counter->str, '='))
	{
		node = (t_env*)malloc(sizeof(t_env));
		arg = ft_split(counter->str, '=');
		node->variable = ft_strdup(arg[0]);
		node->value = ft_strdup(arg[1]);
		node->next = NULL;
		push_back_ex(&g_variables, node, arg);
		ft_free_star(arg);
		return (1);
	}
	return (0);
}

char	*help_convert(t_command *head)
{
	t_command	*counter;
	int			r;

	counter = head;
	if (!(r = help_convert2(counter)) && counter->str != NULL &&
	!ft_strcmp("export", counter->str))
	{
	}
	else if (r == 1)
		return (NULL);
	return (counter->str);
}

char	**help_convert1(t_command *counter)
{
	char	*tmp;
	int		i;

	ft_memset(g_argv, 0, 4096);
	i = 0;
	while (counter && !(counter->what == PIPE || counter->what == SEMICOL))
	{
		if (do_somein_1(&counter) == -1 || do_someout_1(&counter) == -1)
			return (NULL);
		if (counter->what == COMMAND && to_lower(&counter) == 1)
		{
			tmp = NULL;
			if ((help_convert(counter) == NULL)
			|| !(g_argv[i] = path(counter->str)))
				return (NULL);
		}
		else if (counter->what != REDIN && counter->what != REDOUT
		&& counter->what != DOUBLEREDOUT && !g_mul_redin && !g_multi_redout)
			g_argv[i] = ft_strdup(counter->str);
		counter = counter->next;
		i++;
	}
	g_argv[i] = NULL;
	return (g_argv);
}

char	**convert(t_command *head)
{
	t_command *counter;

	counter = head;
	if (counter != NULL && counter->what == REDOUT)
	{
		if (!do_someout(&counter))
			return (NULL);
		else
			return (g_argv);
	}
	if (counter != NULL && counter->what == REDIN)
	{
		if (!do_somein(&counter))
			return (NULL);
		else
			return (g_argv);
	}
	return (help_convert1(counter));
}
