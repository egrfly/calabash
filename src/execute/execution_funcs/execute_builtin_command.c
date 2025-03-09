/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:27:50 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 19:09:44 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../parse/parse.h"
#include "../builtins/builtins.h"
#include "../redirection_utils/redirection_utils.h"

static const
	t_builtin_cmd_function
	g_builtin_cmd_functions[] = {
[BUILTIN_ECHO] = builtin_echo,
[BUILTIN_CD] = builtin_cd,
[BUILTIN_PWD] = builtin_pwd,
[BUILTIN_EXPORT] = builtin_export,
[BUILTIN_UNSET] = builtin_unset,
[BUILTIN_ENV] = builtin_env,
[BUILTIN_EXIT] = builtin_exit,
[BUILTIN_HISTORY] = builtin_history,
};

int	execute_builtin_command(
		const char *command,
		const char **argv,
		t_program_vars *program_vars,
		t_list *redirections)
{
	t_builtins	index;
	int			return_status;

	index = get_builtin_cmd_index(command);
	if (index != BUILTIN_NOT_FOUND)
	{
		if (!perform_redirections(redirections))
			return (free(argv), GENERAL_FAILURE);
		else
		{
			return_status = g_builtin_cmd_functions[index](argv, program_vars);
			revert_redirections(redirections);
			return (free(argv), return_status);
		}
	}
	else
		return (free(argv), NOT_FOUND);
}
