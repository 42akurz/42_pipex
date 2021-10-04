/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 07:58:42 by akurz             #+#    #+#             */
/*   Updated: 2021/09/15 11:39:35 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	*check_commandpath(int rows, char **paths, char **cmd)
{
	int		i;
	char	*ret;
	char	*slash;

	i = 0;
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd[0]);
		if (access(ret, F_OK) != -1)
		{
			return (ret);
		}
		i++;
	}
	ft_putstr_fd("command not found\n", 2);
	exit(0);
}

void	execute(char **cmd, char **envp)
{
	char	*pathname;
	char	**paths;
	char	*cmdpath;
	int		x;
	int		rowsinpath;

	rowsinpath = 0;
	x = 0;
	while (envp[x] != NULL)
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'A'
		&& envp[x][2] == 'T' && envp[x][3] == 'H')
		{
			pathname = ft_substr(envp[x], 5, ft_strlen(envp[x]) - 5);
			paths = ft_split(pathname, ':');
			rowsinpath = countrows(paths);
			cmdpath = check_commandpath(rowsinpath, paths, cmd);
			execve(cmdpath, cmd, envp);
		}
		x++;
	}
}

void	child(t_vars *vars, int argc, char **argv, char **envp)
{
	char	**cmd;
	int		output;

	cmd = ft_split(argv[vars->x], ' ');
	close(vars->pipes[0]);
	dup2(vars->temp_fd, 0);
	close(vars->temp_fd);
	dup2(vars->pipes[1], 1);
	close(vars->pipes[1]);
	if (vars->processes == 0)
	{
		output = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0666);
		dup2(output, 1);
	}
	execute(cmd, envp);
}

void	parent(t_vars *vars)
{
	close(vars->pipes[1]);
	close(vars->temp_fd);
	dup2(vars->pipes[0], vars->temp_fd);
	close(vars->pipes[0]);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;

	vars.processes = argc - 4;
	if (argc < 5)
	{
		ft_putstr_fd("ERROR\nusage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		exit(0);
	}
	handle_infile(&vars, argv);
	vars.x = 2;
	while (vars.processes >= 0)
	{
		pipe_n_fork(&vars);
		if (vars.childpid == 0)
			child(&vars, argc, argv, envp);
		else
		{
			wait(NULL);
			parent(&vars);
		}
		vars.processes--;
		vars.x++;
	}
	return (0);
}
