/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:26:24 by akurz             #+#    #+#             */
/*   Updated: 2021/09/30 16:14:08 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_vars
{
	int		pipes[2];
	pid_t	childpid;
	int		processes;
	int		x;
	int		input;
	int		temp_fd;
}			t_vars;

int		main(int argc, char **argv, char **envp);

/* Opens infile, checks if it's valid and creates temp_fd. */
void	handle_infile(t_vars *vars, char **argv);

/* Creating a pipe with with two (fd ends).
Forking to create 2 seperate processes. */
void	pipe_n_fork(t_vars *vars);

/* Redirects input and output.
Calls the execute function. */
void	child(t_vars *vars, int argc, char **argv, char **envp);

/* Gets command name and command path.
Executes the command which is going to kill the child process. */
void	execute(char **cmd, char **envp);

/* Checks if the command is valid and accessable. */
char	*check_commandpath(int rows, char **paths, char **cmd);

/* Waiting for the child to execute/die.
Then redirecting the ouput of the dead child to input of upcoming child. */
void	parent(t_vars *vars);

/* Counts the number of paths in (env) */
int		countrows(char **paths);

#endif 