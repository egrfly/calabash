/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 16:30:16 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "ft_stdio.h"
#include "../execution_funcs/execution_funcs.h"

int	builtin_export(
		const char **argv, t_program_vars *program_vars)
{
	(void)argv;
	(void)program_vars;
	ft_dprintf(STDOUT_FILENO, "builtin_export\n");
	return (0);
}
