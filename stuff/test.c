/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkrusta <gkrusta@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:18:45 by gkrusta           #+#    #+#             */
/*   Updated: 2023/09/01 12:08:17 by gkrusta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv)
{
	int	id;

	id = fork();
	if (id != 0)
	{
		fork();
		puts("created second fork\n");
	}
	printf("abc\n");
	return (0);
}