/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:00:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 09:55:01 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../assignment_utils/assignment_utils.h"
#include "../list_utils/list_utils.h"
#include "../path_utils/path_utils.h"
#include "./command_utils.h"

bool	init_exec_params(
			t_exec_params *exec_params,
			t_list *arguments,
			t_list *assignments,
			t_list *env)
{
	t_list	*env_with_new_assignments;
	t_list	*new_assignments;

	ft_bzero(exec_params, sizeof(t_exec_params));
	env_with_new_assignments = ft_list_shallowcopy(env);
	new_assignments = ft_list_shallowcopy(assignments);
	if (!env_with_new_assignments || !new_assignments)
	{
		ft_list_destroy(env_with_new_assignments, NULL);
		ft_list_destroy(new_assignments, NULL);
		return (false);
	}
	ft_list_merge(env_with_new_assignments, new_assignments);
	filter_out_duplicate_assignments(env_with_new_assignments);
	exec_params->command = arguments->first->value;
	exec_params->path = NULL;
	exec_params->args = get_values_from_list(arguments);
	exec_params->envp = get_values_from_list(env_with_new_assignments);
	ft_list_destroy(env_with_new_assignments, NULL);
	return (exec_params->args && exec_params->envp && get_full_command_path(
			&exec_params->path, arguments->first->value,
			get_path_variable(env)));
}
