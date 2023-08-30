/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: honer <honer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:54:37 by honer             #+#    #+#             */
/*   Updated: 2023/05/03 00:41:10 by honer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_heredoc(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	heredoc(char *endline)
{
	char		*input;
	static int	start = 0;

	if (start)
		close(g_ms.heredoc_fd[0]);
	start = 1;
	if (pipe(g_ms.heredoc_fd) < 0)
		return (perror("minishell"));
	while (1)
	{
		signal(SIGINT, &close_heredoc);
		input = readline("heredoc>> ");
		if (!input || ft_strcmp(input, endline) || g_ms.ignore)
		{
			free(input);
			break ;
		}
		write(g_ms.heredoc_fd[1], input, ft_strlen(input));
		write(g_ms.heredoc_fd[1], "\n", 1);
		free(input);
	}
	close(g_ms.heredoc_fd[1]);
}
