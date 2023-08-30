/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekahram <sekahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:03 by honer             #+#    #+#             */
/*   Updated: 2023/07/27 02:08:28 by honer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_env(char *data)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_calloc(sizeof(char *), env_len() + 1);
	while (g_ms.env[i])
	{
		if (ft_strncmp(g_ms.env[i], data, ft_strlen(data)))
		{
			new_env[j] = ft_strdup(g_ms.env[i]);
			j++;
		}
		i++;
	}
	new_env[j] = 0;
	free_array(g_ms.env);
	g_ms.env = new_env;
}

void	builtin_unset(char **input, int cntrl)
{
	char	*data;

	input++;
	while (*input)
	{
		data = ft_strjoin(*input, "=");
		remove_env(data);
		free(data);
		input++;
	}
	set_paths();
	if (cntrl == 0)
		exit(EXIT_SUCCESS);
}

int	env_len(void)
{
	char	**env;

	env = g_ms.env;
	while (*env)
		env++;
	return (env - g_ms.env);
}

int	is_include(char *str, int cntrl)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	env = g_ms.env;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && str[j])
		{
			if (str[j] == '=' && env[i][j] == '=')
				return (i);
			if (str[j] != env[i][j])
				break ;
			j++;
		}
		i++;
	}
	if (env_len2(str, 1, cntrl))
		return (env_len2(str, 1, cntrl));
	return (-1);
}

int	ft_strcomp(char *s1)
{
	while (*s1)
	{
		if (*s1 == '=')
			return (0);
		s1++;
	}
	return (1);
}
