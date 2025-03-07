/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/07 08:38:25 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "builtins.h"
#include "ft_stdio.h"
#include "ft_string.h"

bool	dash_n_is_present(const char *argument)
{
	if (!argument)
		return (false);
	if (argument
		&& argument[0] == '-'
		&& argument[1] == 'n'
		&& argument[2] == '\0')
		return (true);
	return (false);
}

/* TODO: beat the trivial! Such a simple function and it still does not
 *		 want to work, properly??!?
 */
int	builtin_echo(
		const char **argv, t_program_name_and_env *program_name_and_env)
{
	int	i;

	(void)program_name_and_env;
	i = 1;
	if (dash_n_is_present(argv[i]))
		i++;
	while (argv[i])
	{
		ft_dprintf(STDOUT_FILENO, "%s", argv[i]);
		if (argv[i + 1])
			ft_dprintf(STDOUT_FILENO, " ");
		fflush(stdout);
		i++;
	}
	if (argv[1] && (ft_strcmp(argv[1], "-n") != 0))
		ft_dprintf(STDOUT_FILENO, "\n");
	//ft_dprintf(STDOUT_FILENO, "\n");
	return (SUCCESS);
}
