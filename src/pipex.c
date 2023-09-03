/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:47:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/03 20:54:31 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_search(t_pipex p, char **envp)
{
	int	index;

	index = 0;
	while (envp[index])
	{
		if (strncmp(envp[index], "PATH=", 5) == 0)
		{
			p.path = envp[index] + 5;
			break ;
		}
		index++;
	}
	if (!p.path)
		ft_error_msg("Error: ");
	return (p.path);
}

char	*command_append(t_pipex p, char *cmd1)
{
	int		index;
	//char	split_result;
	//char	*cmd1_with_slash;
	char	*saver;

	index = 0;
	p.cmd = ft_split(p.path, ':');
	p.cmd1_with_slash = ft_strjoin("/", cmd1);
	while (p.cmd[index])
	{
		saver = p.cmd[index];
		p.path = ft_strjoin(p.cmd[index], p.cmd1_with_slash);
		if (access(p.cmd[index], X_OK) == 0)
			return (p.path);
		free(saver);
		index++;
	}
	exit (1);
}

void	child_process(t_pipex p, char **envp)
{
	if (dup2(p.infile_fd, STDIN_FILENO) == -1)
		ft_error_msg("Error: ");
	if (dup2(p.end[1], STDOUT_FILENO) == -1)
		ft_error_msg("Error: ");
	close (p.end[0]);
	close (p.infile_fd);
	if (execve(p.path, p.cmd1_with_slash, envp) == -1)
		ft_msg_error("execve: ");
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc != 5)
		return (1);
	p.infile_fd = open(argv[1], O_RDONLY);
	if (p.infile_fd == -1)
		return (1);
	if (access(argv[1], R_OK) == -1)
		exit (1);
	pipe(p.end);
	p.pid = fork();
	if (p.pid == -1)
		ft_error_msg("Error: ");
	path_search(p, envp);
	command_append(p, argv[2], envp);
	if (p.pid == 0) // child process
		child_process(p, envp);
	else
	{
		waitpid
		parent_process();
	}
	return (0);
}

/* 
char	**path_search(char * command, char ** envp)
{
	char ** split_result;
	unsigned int index = 0;
	char * path;

	envp == char **
	envp[index] == char *
	while (envp[index])
	{
		if (envp[index] == "PATH=")
		{
			path = envp[index];
			break ;
		}
		index++;
	}
	path = ft_substr (path, 5, strlen(path));
	
	index = 0;
	split_result = ft_split (path, ':');
	char * command_with_slash = ft_strjoin ("/", command );
	char * saver;
	while (split_result[index])
	{
		saver = split_result[index];
		
		split_result[index] = strjoin (split_result[index], command_with_slash);
		
		free (saver);
		index++;
	}
}
 */