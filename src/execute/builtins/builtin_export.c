/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/07 00:46:58 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "ft_stdio.h"

int	builtin_export(
		const char **argv, t_program_name_and_env *program_name_and_env)
{
	(void)argv;
	(void)program_name_and_env;
	ft_dprintf(STDOUT_FILENO, "builtin_export\n");
	return (0);
}
