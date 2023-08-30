/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekahram <sekahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:03 by honer             #+#    #+#             */
/*   Updated: 2023/07/24 14:01:06 by sekahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_ms;

void	init_app(char **env)
{
	errno = 0;
	g_ms.paths = NULL;
	set_env(env);
	set_paths();
}

void	init_shell(char *input)
{
	g_ms.token = NULL;
	g_ms.ignore = FALSE;
	g_ms.process = NULL;
	g_ms.process_count = 0;
	g_ms.ex_flag = 0;
	tokenize(input);
	if (!lexer())
		return ;
	start_cmd();
	free_process();
}

void	ctrl_c(int sig)
{
	(void)sig;
	g_ms.ignore = TRUE;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	write(1, "\033[A", 3);
}

void	ctrl_d(char *input)
{
	if (!input)
	{
		printf("exit\n");
		exit(errno);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*input;

	init_app(env);
	while (ac && av)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		write(1, "\033[32m", 5);
		input = readline("minishell_> ");
		write(1, "\033[0m", 4);
		ctrl_d(input);
		if (g_ms.ignore)
		{
			g_ms.ignore = FALSE;
			free(input);
			input = ft_calloc(sizeof(char *), 1);
		}
		if (*input)
		{
			init_shell(input);
			add_history(input);
		}
		free(input);
	}
	exit(errno);
}
