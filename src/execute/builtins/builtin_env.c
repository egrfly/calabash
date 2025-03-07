/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/07 08:40:18 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"
#include "ft_stdio.h"
#include "ft_list.h"

int	builtin_env(
		const char **argv, t_program_name_and_env *program_name_and_env)
{
	t_list_node	*list_node;

	(void)argv;
	if (!program_name_and_env->env)
		return (GENERAL_FAILURE);
	list_node = program_name_and_env->env->first;
	while (list_node)
	{
		ft_dprintf(STDOUT_FILENO, "%s\n", list_node->value);
		list_node = list_node->next;
	}
	return (SUCCESS);
}
