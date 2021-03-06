/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hope.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:51:56 by oel-bour          #+#    #+#             */
/*   Updated: 2020/03/09 16:13:10 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	help_the_main(void)
{
	while (g_var.j < g_var.nb_pipe)
	{
		g_p = 1;
		g_var.arg = NULL;
		g_var.arg = convert(g_var.pipe[g_var.j]);
		if (!g_var.arg)
			break ;
		ft_exx(g_var.arg, g_var.j, g_var.nb_pipe);
		ft_free_star_ok(g_var.arg);
		g_var.j++;
	}
}

void	waitall(int g)
{
	int f;
	int i;

	f = 0;
	while (f < g)
	{
		close(g_dff[f][0]);
		close(g_dff[f][1]);
		f++;
	}
	i = 0;
	while (i < g)
	{
		wait(&g_status);
		if (WIFEXITED(g_status))
			g_status = WEXITSTATUS(g_status);
		i++;
	}
}

int		help_the_main1(void)
{
	if (g_var.semi[g_var.i] != NULL)
	{
		g_var.j = 0;
		g_var.arg = NULL;
		g_var.pipe = get_pipe(g_var.semi[g_var.i], &g_var.nb_pipe);
		if (g_p == 0)
		{
			if (!(g_var.arg = convert(g_var.pipe[g_var.j])))
				return (1);
			ft_exx(g_var.arg, -1, -1);
			ft_free_star_ok(g_var.arg);
			waitall(1);
		}
		else
		{
			help_the_main();
			waitall(g_var.j);
		}
		g_p = 0;
	}
	return (0);
}

int		the_main(t_command *head)
{
	g_argv = (char**)ft_calloc(4096, sizeof(char*));
	if (head == NULL)
		return (0);
	init_t_vars(&g_var);
	g_var.semi = get_semi(head, &g_var.nb_semi);
	while (g_var.i < g_var.nb_semi)
	{
		g_status = (g_status == 258) ? 258 : 0;
		help_the_main1();
		free(g_var.pipe);
		g_var.i++;
	}
	free(g_argv);
	free(g_var.semi);
	return (0);
}
