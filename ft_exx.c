/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bour <oel-bour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:28:42 by oel-bour          #+#    #+#             */
/*   Updated: 2020/02/04 21:40:32 by oel-bour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end(int last, int input, int fd[2])
{
	if (last == 1)
		close(fd[0]);
	if (input != 0)
		close(input);
	close(fd[1]);
	return (fd[0]);
}

void	dupx(int first, int last, int input, int fd[2])
{
	if (first == 1 && last == 0 && input == 0)
		dup2(fd[1], 1);
	else if (first == 0 && last == 0 && input != 0)
	{
		dup2(input, 0);
		dup2(fd[1], 1);
	}
	else
		dup2(input, 0);
	if (g_multi_redout == 1)
		dup2(g_out_fd, 1);
	if (g_mul_redin == 1)
		dup2(g_in_fd, 0);
}

int		built(char **arg)
{
	if (!ft_strcmp(arg[0], "echo"))
		return (echo(arg));
	if (!ft_strcmp(arg[0], "pwd"))
		return (pwd(1));
	if (!ft_strcmp(arg[0], "cd"))
		return (cd(arg[1]));
	if (!ft_strcmp(arg[0], "env"))
		return (env(environt));
	if (!ft_strcmp(arg[0], "exit"))
	{
		ft_lstclear_command(&command);
		exit(0);
	}
	if (!ft_strcmp(arg[0], "export"))
		return (export(arg));
	if (!ft_strcmp(arg[0], "unset"))
		return (unset(arg));
	if (!ft_strcmp(arg[0], "var"))
		return (env_var(variables));
	return (1);
}

int		built_child(char **arg)
{
	if (!ft_strcmp(arg[0], "cd"))
		cd(arg[1]);
	else if (!ft_strcmp(arg[0], "pwd"))
		pwd(1);
	else if (!ft_strcmp(arg[0], "echo"))
		echo(arg);
	else if (!ft_strcmp(arg[0], "env"))
		env(environt);
	else if (!ft_strcmp(arg[0], "unset"))
		unset(arg);
	else if (!ft_strcmp(arg[0], "export"))
		export(arg);
	if (is_cmd(arg[0]))
		exit(0);
	return (1);
}

void	close_fd(void)
{
	if (g_multi_redout == 1)
	{
		close(g_out_fd);
		g_multi_redout = 0;
	}
	if (g_mul_redin == 1)
	{
		close(g_in_fd);
		g_mul_redin = 0;
	}
}

int		child(char **arg, int first, int last, int input)
{
	dupx(first, last, input, g_fd);
	if (built_child(arg))
	{
		if (execve(arg[0], &arg[0], environ))
			perror("exceve");
	}
	close_fd();
	return (1);
}

int   ft_exx(char **arg, int first, int last, int input)
{
	int g_status;

	if (arg == NULL || arg[0] == NULL)
		return (-1);
	pipe(g_fd);
	if (is_cmd(arg[0]) && g_p == 0 && g_multi_redout == 0 && g_mul_redin == 0)
		return (built(arg));
	if ((g_pid = fork()) == -1)
	{
		perror("fork");
		return (1);
	}
	else if (g_pid == 0)
		return (child(arg, first, last, input));
	else
		waitpid(g_pid, &g_status, 0);
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	close_fd();
	g_multi_redout = 0;
	g_mul_redin = 0;
	return (end(last, input, g_fd));
}