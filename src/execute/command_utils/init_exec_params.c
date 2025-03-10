/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 03:00:45 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 15:18:38 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "ft_string.h"
#include "../../interface/list_utils/list_utils.h"
#include "../path_utils/path_utils.h"
#include "../var_utils/var_utils.h"
#include "./command_utils.h"

static const
	char
	*g_colourisable_commands[] = {
	"ls",
	"dir",
	"vdir",
	"grep",
	"fgrep",
	"egrep",
};

static t_list	*get_env_with_new_assignments(
					t_list *vars,
					t_list *assignments)
{
	t_list		*env_with_new_assignments;
	t_list_node	*new_assignment_node;

	env_with_new_assignments = get_exported_vars(vars);
	if (!env_with_new_assignments)
		return (NULL);
	new_assignment_node = assignments->first;
	while (new_assignment_node)
	{
		if (!upsert_var(new_assignment_node->value, env_with_new_assignments,
				EXPORTED))
			return (ft_list_destroy(env_with_new_assignments, NULL), NULL);
		new_assignment_node = new_assignment_node->next;
	}
	return (env_with_new_assignments);
}

static t_list	*get_arguments_with_colourisation(
					char *path,
					t_list *arguments)
{
	t_list	*arguments_with_colourisation;
	char	*current_command_suffix;
	size_t	i;

	arguments_with_colourisation = ft_list_shallowcopy(arguments);
	if (!arguments_with_colourisation)
		return (NULL);
	if (!path)
		return (arguments_with_colourisation);
	i = 0;
	while (i < sizeof(g_colourisable_commands) / sizeof(char *))
	{
		current_command_suffix = ft_strjoin("bin/", g_colourisable_commands[i]);
		if (!current_command_suffix)
			return (arguments_with_colourisation);
		if (ft_strends(path, current_command_suffix))
		{
			ft_list_insert(arguments_with_colourisation, 1, "--color=auto");
			free(current_command_suffix);
			break ;
		}
		free(current_command_suffix);
		i++;
	}
	return (arguments_with_colourisation);
}

bool	init_exec_params(
			t_exec_params *exec_params,
			t_list *arguments,
			t_list *assignments,
			t_list *vars)
{
	t_list	*arguments_with_colourisation;
	t_list	*env_with_new_assignments;

	ft_bzero(exec_params, sizeof(t_exec_params));
	exec_params->command = arguments->first->value;
	if (!get_full_command_path(&exec_params->path, exec_params->command,
			get_var_value("PATH", vars)))
		return (false);
	arguments_with_colourisation = get_arguments_with_colourisation(
			exec_params->path, arguments);
	env_with_new_assignments = get_env_with_new_assignments(vars, assignments);
	if (arguments_with_colourisation && env_with_new_assignments)
	{
		exec_params->args = get_values_from_list(arguments_with_colourisation);
		exec_params->envp = get_values_from_list(env_with_new_assignments);
	}
	ft_list_destroy(arguments_with_colourisation, NULL);
	ft_list_destroy(env_with_new_assignments, NULL);
	return (exec_params->args && exec_params->envp);
}
