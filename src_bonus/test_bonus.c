/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:03:55 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/10 19:07:29 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_child(t_pipex *p)
{
	close (p->end[1]);
	if (dup2(p->end[0], STDIN_FILENO) == -1)
		ft_error_msg("mid: ");
}
void	last_process(t_pipex *p, char **envp, char *cmd_last)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		command_append(p, cmd_last);
		close (p->end[0]);
		if (dup2(p->outfile_fd, STDOUT_FILENO) == -1)
			ft_error_msg("last: ");
		close (p->outfile_fd);
		if (execve(p->cmd, p->cmd_arg, envp) == -1)
			ft_error_msg("Execve: ");
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
			middle_child(p);
	}
}

void	ft_leaks(void)
{
	system("leaks -q pipex_bonus");
}

void	pipex_bonus(t_pipex *p, char **argv, char **envp, int argc)
{
	pid_t	pid;

	printf("argv is %d\n", p->i);
	while (p->i < argc - 2)
	{
		pipe(p->end);
		pid = fork();
		ft_printf("pid is %d\n", pid);
		if (pid == -1)
			ft_error_msg("pid: ");
		if (pid == 0)
		{
			command_append(p, argv[p->i]);
			ft_printf("after append\n");
			close (p->end[0]);
			if (dup2(p->end[1], STDOUT_FILENO) == -1)
				ft_error_msg("Dup2: ");
			if (execve(p->cmd, p->cmd_arg, envp) == -1)
				ft_error_msg("child: ");
		}
		else
		{
			//wait(NULL);
			waitpid(pid, NULL, WNOHANG);
			middle_child(p);
		}
		p->i++;
	}
		waitpid(-1, NULL, 0);
		ft_printf("pid -> %i\n", pid);
		last_process(p, envp, argv[argc -2]);

}

void	here_doc(t_pipex *p, char **file)
{
	char	*limiter;
	char	*line;

	limiter = file[2];
	pipe(p->end);
	while (1)
	{
		line = get_next_line(0);
		if (strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free (line);
			break ;
		}
		write (p->end[1], line, ft_strlen(line));
		free (line);
	}
	close (p->end[1]);
}

void	openfile(t_pipex *p, char **file, int argc)
{
	if (strncmp(file[1], "here_doc", 9) == 0)
	{
		here_doc(p, file);
		if (dup2(p->end[0], STDIN_FILENO) == -1)
			ft_error_msg("Dup2: ");
		close (p->end[0]);
		p->i = 3;
	}
	else
	{
		p->infile_fd = open(file[1], O_RDONLY, 0444);
		if (dup2(p->infile_fd, STDIN_FILENO) == -1)
			ft_error_msg("Dup2: ");
		close (p->infile_fd);
		p->i = 2;
	}
	p->outfile_fd = open(file[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	atexit(ft_leaks);

	p = malloc(sizeof(t_pipex));
	if (argc > 4)
	{
		openfile(p, argv, argc);
		path_search(p, envp);
		pipex_bonus(p, argv, envp, argc);
		waitpid(-1, NULL, 0);
	}
	puts("end\n");
	ft_free_argv(p);
	return (0);
}
