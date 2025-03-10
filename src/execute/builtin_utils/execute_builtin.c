/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:24:37 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 01:18:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../execute.h"
#include "../builtin_funcs/builtin_funcs.h"
#include "./builtin_utils.h"

static const
	t_execution_func
	g_builtin_funcs[] = {
[BUILTIN_COLON] = NULL,
[BUILTIN_DOT] = NULL,
[BUILTIN_ALIAS] = NULL,
[BUILTIN_BG] = NULL,
[BUILTIN_BIND] = NULL,
[BUILTIN_BUILTIN] = NULL,
[BUILTIN_CALLER] = NULL,
[BUILTIN_CD] = builtin_cd,
[BUILTIN_COMMAND] = NULL,
[BUILTIN_COMPGEN] = NULL,
[BUILTIN_COMPLETE] = NULL,
[BUILTIN_COMPOPT] = NULL,
[BUILTIN_DECLARE] = NULL,
[BUILTIN_DIRS] = NULL,
[BUILTIN_DISOWN] = NULL,
[BUILTIN_ECHO] = builtin_echo,
[BUILTIN_ENABLE] = NULL,
[BUILTIN_ENV] = builtin_env,
[BUILTIN_EVAL] = NULL,
[BUILTIN_EXEC] = NULL,
[BUILTIN_EXIT] = builtin_exit,
[BUILTIN_EXPORT] = builtin_export,
[BUILTIN_FC] = NULL,
[BUILTIN_FG] = NULL,
[BUILTIN_GETOPTS] = NULL,
[BUILTIN_HASH] = NULL,
[BUILTIN_HELP] = NULL,
[BUILTIN_HISTORY] = builtin_history,
[BUILTIN_JOBS] = NULL,
[BUILTIN_LET] = NULL,
[BUILTIN_LOCAL] = NULL,
[BUILTIN_LOGOUT] = NULL,
[BUILTIN_MAPFILE] = NULL,
[BUILTIN_POPD] = NULL,
[BUILTIN_PUSHD] = NULL,
[BUILTIN_PWD] = builtin_pwd,
[BUILTIN_READ] = NULL,
[BUILTIN_READARRAY] = NULL,
[BUILTIN_READONLY] = NULL,
[BUILTIN_RETURN] = NULL,
[BUILTIN_SET] = NULL,
[BUILTIN_SHIFT] = NULL,
[BUILTIN_SHOPT] = NULL,
[BUILTIN_SOURCE] = NULL,
[BUILTIN_SUSPEND] = NULL,
[BUILTIN_TIMES] = NULL,
[BUILTIN_TRAP] = NULL,
[BUILTIN_TYPE] = NULL,
[BUILTIN_TYPESET] = NULL,
[BUILTIN_ULIMIT] = NULL,
[BUILTIN_UMASK] = NULL,
[BUILTIN_UNALIAS] = NULL,
[BUILTIN_UNSET] = builtin_unset,
[BUILTIN_WAIT] = NULL,
};

int	execute_builtin(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_builtin					builtin;
	t_execution_func			builtin_func;

	node_value = node->value;
	builtin = get_builtin(node_value->arguments->first->value);
	builtin_func = g_builtin_funcs[builtin];
	if (!builtin_func)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
				get_program_name(), node_value->arguments->first->value,
				"builtin not supported"), GENERAL_FAILURE);
	return (builtin_func(node, fixed_program_elements, program_vars));
}
