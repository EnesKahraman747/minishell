/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sekahram <sekahram@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:53:58 by sekahram          #+#    #+#             */
/*   Updated: 2023/07/24 14:25:10 by sekahram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_paths(void)
{
	char	*path;

	if (g_ms.paths)
		free_array(g_ms.paths);
	path = get_env("PATH");
	if (!(*path))
		g_ms.paths = NULL;
	else
		g_ms.paths = ft_split(path, ':');
	free(path);
}
