/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 16:30:29 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../main.h"
#include "builtins.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../execution_funcs/execution_funcs.h"

bool	dash_n_is_present(const char *argument)
{
	int	i;

	if (!argument)
		return (false);
	if (argument
		&& argument[0] == '-'
		&& argument[1] == 'n')
	{
		i = 2;
		while (argument[i] && argument[i] == 'n')
			i++;
		if (argument[i] == '\0')
			return (true);
	}
	return (false);
}

int	builtin_echo(
		const char **argv, t_program_vars *program_vars)
{
	int		i;
	bool	skip_print_last_new_line;

	(void)program_vars;
	skip_print_last_new_line = (argv[1] && dash_n_is_present(argv[1]));
	i = 1;
	if (argv[1] && dash_n_is_present(argv[i]))
		i++;
	while (argv[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", argv[i]);
		if (argv[i + 1])
			ft_dprintf(STDOUT_FILENO, " ");
		fflush(stdout);
		i++;
	}
	if (!skip_print_last_new_line)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (SUCCESS);
}
