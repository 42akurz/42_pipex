/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:31:58 by akurz             #+#    #+#             */
/*   Updated: 2021/09/15 11:32:43 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

void	pipe_n_fork(t_vars *vars)
{
	if (pipe(vars->pipes) == -1)
	{
		perror("pipe");
		exit(0);
	}
	vars->childpid = fork();
	if (vars->childpid == -1)
	{
		perror("fork");
		exit(0);
	}
}

void	handle_infile(t_vars *vars, char **argv)
{
	vars->input = open(argv[1], 0);
	if (vars->input == -1)
	{
		perror("");
		exit(0);
	}
	vars->temp_fd = dup(vars->input);
	close(vars->input);
}
