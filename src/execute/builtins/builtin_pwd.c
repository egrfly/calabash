/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/08 17:32:13 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"
#include "ft_stdio.h"

int	builtin_pwd(
		const char **argv, t_program_vars *program_vars)
{
	(void)argv;
	(void)program_vars;
	ft_dprintf(STDOUT_FILENO, "%s\n", getcwd(NULL, 0));
	return (0);
}
