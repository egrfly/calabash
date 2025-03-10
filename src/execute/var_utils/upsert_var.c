/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upsert_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:31:49 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 23:21:39 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../parse/word_utils/word_utils.h"
#include "./var_utils.h"

static bool	change_var_export_mode(
				t_export_mode mode,
				t_list_node	*current_var_node)
{
	char	*current_var;
	char	*new_var;

	current_var = current_var_node->value;
	if (mode == EXPORTED
		&& ft_strstarts(current_var, NOT_EXPORTED_PREFIX))
		new_var = ft_substr(current_var, 1, ft_strlen(&current_var[1]));
	else if (mode == NOT_EXPORTED
		&& !ft_strstarts(current_var, NOT_EXPORTED_PREFIX))
		new_var = ft_strjoin(NOT_EXPORTED_PREFIX, current_var);
	else
		return (true);
	if (!new_var)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	free(current_var);
	current_var_node->value = new_var;
	return (true);
}

static bool	update_var(
				t_export_mode mode,
				t_list_node	*current_var_node,
				char *var)
{
	char	*current_var;
	char	*new_var;

	current_var = current_var_node->value;
	if (mode == NOT_EXPORTED
		|| ((mode == UNCHANGED_OR_EXPORTED
				|| mode == UNCHANGED_OR_NOT_EXPORTED)
			&& ft_strstarts(current_var, NOT_EXPORTED_PREFIX)))
		new_var = ft_strjoin(NOT_EXPORTED_PREFIX, var);
	else
		new_var = ft_strdup(var);
	if (!new_var)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	free(current_var);
	current_var_node->value = new_var;
	return (true);
}

static bool	insert_var(
				t_export_mode mode,
				char *var,
				t_list *vars)
{
	char	*new_var;

	if (mode == NOT_EXPORTED
		|| mode == UNCHANGED_OR_NOT_EXPORTED)
		new_var = ft_strjoin(NOT_EXPORTED_PREFIX, var);
	else
		new_var = ft_strdup(var);
	if (!new_var || !ft_list_append(vars, new_var))
		return (free(new_var), ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	return (true);
}

bool	upsert_var(
			char *var,
			t_list *vars,
			t_export_mode mode)
{
	size_t		var_name_length;
	t_list_node	*current_var_node;

	var_name_length = ft_strcspn(var, "=");
	if (!range_is_identifier(var, 0, var_name_length))
		return (ft_dprintf(STDERR_FILENO,
				"%s: export: `%s': not a valid identifier\n",
				get_program_name(), var), false);
	current_var_node = vars->first;
	while (current_var_node)
	{
		if (vars_have_same_name(var, current_var_node->value))
		{
			if (var[var_name_length] == '=')
				return (update_var(mode, current_var_node, var));
			else
				return (change_var_export_mode(mode, current_var_node));
		}
		current_var_node = current_var_node->next;
	}
	return (insert_var(mode, var, vars));
}
