/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrxy <mrxy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:13:27 by ysarsar           #+#    #+#             */
/*   Updated: 2020/11/23 19:04:02 by mrxy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	void	sh_lunche(char *cmd_name, char **args, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_name, args, env) == -1)
			ft_putendl_fd("21sh: error exec", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putendl_fd("21sh: error forking", 2);
	else
		wait(NULL);
}

static	void	execute_with_path(char **args, char **tabs, t_hash **h_table)
{
	char	*path;

	//path = valid_path(args[0], tabs);
	path = ft_hashtable(args, tabs, h_table);
	if (!path)
	{
		exec_error(args[0], 2);
		return ;
	}
	else if (access(path, X_OK) == 0)
		sh_lunche(path, args, tabs);
	else
		exec_error(path, 1);
}

static	void	execute_without_path(char **args, char **tabs)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
			{
				if (execve(args[0], args, tabs) == -1)
					ft_putendl_fd("21sh: Error exec", 2);
			}
			else
				exec_error(args[0], 1);
		}
		else
			exec_error(args[0], 2);
		exit(1);
	}
	else if (pid < 0)
		ft_putendl_fd("21sh: Error forking.", 2);
	else
		wait(NULL);
}

static	int		check_builtins(char **args, t_env **env, t_hash **h_table)
{
	t_env	*envp;

	envp = *env;
	if (ft_strcmp(args[0], "exit") == 0)
		return (3);
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(*env));
	else if (ft_strcmp(args[0], "setenv") == 0)
		return (ft_setenv(env, args));
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		return (ft_unsetenv(env, args));
	else if (ft_strcmp(args[0], "hash") == 0)
	{
		ft_hash(args, h_table);
		return (1);
	}
	else if (ft_strcmp(args[0], "cd") == 0)
	{
		ft_cd(args, envp);
		return (1);
	}
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "test") == 0)
		return (ft_test(args));
	return (0);
}

int				execute_simple_cmd(char *cmd, char **tabs, t_env **envp, t_hash **h_table)
{
	char		**args;
	char		**arr;
	int			i;

	if (cmd[0])
	{
		arr = ft_strsplit(cmd, -1);
		if (!(args = ft_expantions(arr, envp)))
			return (free_tabs2(arr, NULL));
		if ((i = check_builtins(args, envp, h_table)) >= 0)
		{
			if (i == 3)
			{
				free_tabs(args);
				ft_putendl_fd("exit", 2);
				return (0);
			}
			i == 0 ? printf("Success\n") : printf("Failure\n");
		}
		else if (args[0][0] == '/' || args[0][0] == '.')
			execute_without_path(args, tabs);
		else
			execute_with_path(args, tabs, h_table);
		free_tabs2(args, NULL);
	}
	return (1);
}
