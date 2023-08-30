/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekahram <sekahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:03 by honer             #+#    #+#             */
/*   Updated: 2023/07/26 18:27:43 by sekahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_env(char *str, char *env, char *input, int cntrl)
{
	if (g_ms.ex_flag == 2)
		return (ft_strcomp(str));
	if (g_ms.ex_flag == 1)
		return (err_check(str, input, cntrl));
	else if (g_ms.ex_flag == 0)
	{
		if (!str || !env)
			return (0);
		while ((*str || *env) && *env != '=' && *str != '=')
		{
			if (*str != *env)
				return (0);
			env++;
			str++;
		}
		if ((*str == '=' && *env != '=') || (*str != '=' && *env == '='))
		{
			if (*env == '\0' || *str == '\0')
				return (1);
			return (0);
		}
	}
	return (1);
}

int	err_check(char *str, char *input, int cntrl)
{
	if (*str)
	{
		if (*str == '=')
			return (exp_error(input, cntrl));
		if (*str >= '0' && *str <= '9')
			return (exp_error(input, cntrl));
		while (*str)
		{
			if (*str == ' ' || *str == '\t')
				return (exp_error(input, cntrl));
			str++;
		}
	}
	return (1);
}

int	exp_error(char *str, int cntrl)
{
	errno = 1;
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
	if (cntrl == 0)
		exit(errno);
	return (0);
}

void	builtin_export(char **input, int cntrl)
{
	input++;
	if (*input == NULL)
		builtin_env2(cntrl);
	export_while(input, cntrl);
	set_paths();
	if (cntrl == 0)
		exit(EXIT_SUCCESS);
}

void	export_while(char **input, int cntrl)
{
	int		pos;
	char	*tmp;

	while (*input)
	{
		g_ms.ex_flag = 1;
		if (check_env(*input, NULL, *input, cntrl))
		{
			pos = is_include(*input, cntrl);
			if (pos != -1)
			{
				g_ms.ex_flag = 2;
				if (!check_env(*input, NULL, NULL, cntrl))
				{
					tmp = g_ms.env[pos];
					g_ms.env[pos] = ft_strdup(*input);
					free(tmp);
				}
			}
			else
				add_env(*input, cntrl);
		}
		input++;
	}
}
