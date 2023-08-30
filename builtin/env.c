/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekahram <sekahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:03 by honer             #+#    #+#             */
/*   Updated: 2023/07/27 02:05:48 by honer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(int cntrl)
{
	char	**env;

	env = g_ms.env;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	if (cntrl == 0)
	{
		exit(EXIT_SUCCESS);
	}
}

void	add_env(char *str, int cntrl)
{
	int		i;
	char	**env;
	char	**new_env;

	i = 0;
	env = g_ms.env;
	new_env = ft_calloc(sizeof(char **), env_len2(NULL, 0, cntrl) + 2);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	free_array(g_ms.env);
	g_ms.env = new_env;
}

void	env_extra(char **env, int i, int j, int flag)
{
	env = g_ms.env;
	while (env[++i])
	{
		printf("declare -x ");
		while (env[i][++j])
		{
			if (env[i][j - 1] == '=')
			{
				flag = 1;
				printf("\"");
			}
			printf("%c", env[i][j]);
		}
		j = -1;
		if (flag == 1)
		{
			flag = 0;
			printf("\"");
		}
		printf("\n");
	}
}

void	builtin_env2(int cntrl)
{
	env_extra(NULL, -1, -1, 0);
	if (cntrl == 0)
		exit(EXIT_SUCCESS);
}

int	env_len2(char *str, int flag, int cntrl)
{
	char	**env;
	int		i;

	env = g_ms.env;
	if (flag == 0)
	{
		while (*env)
			env++;
		return (env - g_ms.env);
	}
	else
	{
		i = 0;
		while (env[i])
		{
			g_ms.ex_flag = 0;
			if (check_env(str, env[i], NULL, cntrl))
				return (i);
			i++;
		}
	}
	return (0);
}
