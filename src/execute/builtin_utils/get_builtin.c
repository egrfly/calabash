/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:24:39 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 19:52:33 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"
#include "./builtin_utils.h"

static const
	char
	*g_builtins[] = {
[BUILTIN_COLON] = ":",
[BUILTIN_DOT] = ".",
[BUILTIN_ALIAS] = "alias",
[BUILTIN_BG] = "bg",
[BUILTIN_BIND] = "bind",
[BUILTIN_BUILTIN] = "builtin",
[BUILTIN_CALLER] = "caller",
[BUILTIN_CD] = "cd",
[BUILTIN_COMMAND] = "command",
[BUILTIN_COMPGEN] = "compgen",
[BUILTIN_COMPLETE] = "complete",
[BUILTIN_COMPOPT] = "compopt",
[BUILTIN_DECLARE] = "declare",
[BUILTIN_DIRS] = "dirs",
[BUILTIN_DISOWN] = "disown",
[BUILTIN_ECHO] = "echo",
[BUILTIN_ENABLE] = "enable",
[BUILTIN_ENV] = "env",
[BUILTIN_EVAL] = "eval",
[BUILTIN_EXEC] = "exec",
[BUILTIN_EXIT] = "exit",
[BUILTIN_EXPORT] = "export",
[BUILTIN_FC] = "fc",
[BUILTIN_FG] = "fg",
[BUILTIN_GETOPTS] = "getopts",
[BUILTIN_HASH] = "hash",
[BUILTIN_HELP] = "help",
[BUILTIN_HISTORY] = "history",
[BUILTIN_JOBS] = "jobs",
[BUILTIN_LET] = "let",
[BUILTIN_LOCAL] = "local",
[BUILTIN_LOGOUT] = "logout",
[BUILTIN_MAPFILE] = "mapfile",
[BUILTIN_POPD] = "popd",
[BUILTIN_PUSHD] = "pushd",
[BUILTIN_PWD] = "pwd",
[BUILTIN_READ] = "read",
[BUILTIN_READARRAY] = "readarray",
[BUILTIN_READONLY] = "readonly",
[BUILTIN_RETURN] = "return",
[BUILTIN_SET] = "set",
[BUILTIN_SHIFT] = "shift",
[BUILTIN_SHOPT] = "shopt",
[BUILTIN_SOURCE] = "source",
[BUILTIN_SUSPEND] = "suspend",
[BUILTIN_TIMES] = "times",
[BUILTIN_TRAP] = "trap",
[BUILTIN_TYPE] = "type",
[BUILTIN_TYPESET] = "typeset",
[BUILTIN_ULIMIT] = "ulimit",
[BUILTIN_UMASK] = "umask",
[BUILTIN_UNALIAS] = "unalias",
[BUILTIN_UNSET] = "unset",
[BUILTIN_WAIT] = "wait",
[BUILTIN_EXPAND] = "expand",
};

t_builtin	get_builtin(
				char *command)
{
	size_t	i;

	i = 1;
	while (i < sizeof(g_builtins) / sizeof(char *))
	{
		if (!ft_strcmp(command, g_builtins[i]))
			return (i);
		i++;
	}
	return (NOT_A_BUILTIN);
}
