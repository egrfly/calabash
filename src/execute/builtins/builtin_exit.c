/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:10:03 by aistok            #+#    #+#             */
/*   Updated: 2025/03/07 07:17:59 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "builtins.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"

#define SUCCESS 0
#define TOO_MANY_ARGUMENTS 1
#define NUMERIC_ARGUMENT_REQUIRED 2

int	builtin_exit(
		const char **argv, t_program_name_and_env *program_name_and_env)
{
	int	exit_code;

	(void)program_name_and_env;
	exit_code = SUCCESS;
	if (argv[1] && argv[2])
		exit_code = TOO_MANY_ARGUMENTS;
	else if (argv[1] && !ft_atoi(argv[1], &exit_code))
		exit_code = NUMERIC_ARGUMENT_REQUIRED;
	ft_dprintf(STDOUT_FILENO, "exit\n");
	exit((unsigned char)exit_code);
}
