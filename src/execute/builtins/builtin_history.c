/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 23:15:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../execution_funcs/execution_funcs.h"

int	show_usage(const char *cmd_name)
{
	ft_dprintf(STDOUT_FILENO, "Usage:\n");
	ft_dprintf(STDOUT_FILENO, "%s -c\n\n", cmd_name);
	ft_dprintf(STDOUT_FILENO, "Running this command will clear the current"
		" command history.\n", cmd_name);
	return (INCORRECT_USAGE);
}

int	builtin_history(
		char **argv, t_program_vars *program_vars)
{
	(void)argv;
	(void)program_vars;
	if (!argv[1] || !ft_strstr(argv[1], "-c"))
		return (show_usage(argv[0]));
	else
	{
		rl_clear_history();
		ft_printf("Command history now cleared.\n");
	}
	return (SUCCESS);
}
