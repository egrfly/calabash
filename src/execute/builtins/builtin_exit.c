/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:10:03 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 23:15:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../../main.h"
#include "builtins.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include "../execution_funcs/execution_funcs.h"

#define TOO_MANY_ARGUMENTS 1
#define NUMERIC_ARGUMENT_REQUIRED 2

int	builtin_exit(
		char **argv, t_program_vars *program_vars)
{
	int	exit_code;

	(void)program_vars;
	exit_code = SUCCESS;
	if (argv[1] && argv[2])
		exit_code = TOO_MANY_ARGUMENTS;
	else if (argv[1] && !ft_strtoi(argv[1], &exit_code))
		exit_code = NUMERIC_ARGUMENT_REQUIRED;
	ft_dprintf(STDOUT_FILENO, "exit\n");
	exit((unsigned char)exit_code);
}
