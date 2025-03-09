/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/09 23:15:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../main.h"
#include "builtins.h"
#include "ft_stdio.h"
#include "ft_list.h"
#include "../execution_funcs/execution_funcs.h"

int	builtin_env(
		char **argv, t_program_vars *program_vars)
{
	t_list_node	*list_node;

	(void)argv;
	if (!program_vars->env)
		return (GENERAL_FAILURE);
	list_node = program_vars->env->first;
	while (list_node)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", list_node->value);
		list_node = list_node->next;
	}
	return (SUCCESS);
}
