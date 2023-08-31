/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:47:24 by gkrusta           #+#    #+#             */
/*   Updated: 2023/08/31 16:11:00 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char **argv)
{
	int		fd[2];
	pid_t	pid;

	if (argc != 5)
		return (1);
	if (open(fd[1], O_RDONLY) == -1)
		return (1);
	if (access(fd[1], R_OK) == -1)
		exit (1);
	pipe(fd);
	pid = fork();
	if (pid == -1)
		return (perror("After creating fork failed. Error: "));
	if (pid == 0) // child process
		child_process()
	else

	return (0);
}
