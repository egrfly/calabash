/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:27:50 by aistok            #+#    #+#             */
/*   Updated: 2025/03/06 15:32:28 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../interface/interface.h"
#include "./builtins/builtins.h"

static const t_builtin_cmd_function	g_builtin_cmd_functions[] = {
[BUILTIN_ECHO] = builtin_echo,
[BUILTIN_CD] = builtin_cd,
[BUILTIN_PWD] = builtin_pwd,
[BUILTIN_EXPORT] = builtin_export,
[BUILTIN_UNSET] = builtin_unset,
[BUILTIN_ENV] = builtin_env,
[BUILTIN_EXIT] = builtin_exit,
};

/* TODO: CTRL+C CTRL+\ return values for builtins??? */
int	execute_builtin_command(
	const char *command, char *const *argv, char *const *envp)
{
	t_builtins	index;

	index = get_builtin_cmd_index(command);
	if (index != BUILTIN_NOT_FOUND)
		return (g_builtin_cmd_functions[index](argv, envp));
	else
		return (NOT_FOUND);
}
