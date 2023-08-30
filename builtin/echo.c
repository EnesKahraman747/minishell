/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekahram <sekahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:03 by honer             #+#    #+#             */
/*   Updated: 2023/07/26 18:56:11 by sekahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		write(STDOUT_FILENO, &(input[i]), 1);
		i++;
	}
}

int	skip_flag(char **input, int i)
{
	int	j;

	j = 0;
	while (input[i])
	{
		if (input[i][j] == '-')
		{
			j++;
			while (input[i][j] == 'n')
				j++;
			if (input[i][j] != '\0')
				break ;
			if (j == 1)
				break ;
			else
				i++;
			j = 0;
		}
		else
			break ;
	}
	return (i);
}

void	builtin_echo(char **input, int cntrl)
{
	int	i;
	int	flag;

	i = 1;
	flag = TRUE;
	if (input[i])
		i = skip_flag(input, i);
	if (i > 1)
		flag = FALSE;
	errno = 0;
	while (input[i])
	{
		put_char(input[i]);
		if (input[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	if (cntrl == 0)
	{
		exit(EXIT_SUCCESS);
	}
}
