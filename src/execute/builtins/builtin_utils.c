/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:36 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 16:23:05 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include "builtins.h"
#include "ft_string.h"

static const char	*g_builtin_commands[] = {
[BUILTIN_ECHO] = "echo",
[BUILTIN_CD] = "cd",
[BUILTIN_PWD] = "pwd",
[BUILTIN_EXPORT] = "export",
[BUILTIN_UNSET] = "unset",
[BUILTIN_ENV] = "env",
[BUILTIN_EXIT] = "exit",
[BUILTIN_HISTORY] = "history",
};

t_builtins	get_builtin_cmd_index(const char *command)
{
	size_t	i;

	i = 1;
	while (i < sizeof(g_builtin_commands) / sizeof(char *))
	{
		if (ft_strcmp(g_builtin_commands[i], command) == 0)
			return (i);
		i++;
	}
	return (BUILTIN_NOT_FOUND);
}

bool	is_builtin_command(const char *command)
{
	return (get_builtin_cmd_index(command) != BUILTIN_NOT_FOUND);
}
