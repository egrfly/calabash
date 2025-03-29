/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:10:08 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/29 11:29:22 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../interface/interface.h"
#include "./expand.h"
#include "./expand_tildes/expand_tildes.h"
#include "./expand_variables/expand_variables.h"
#include "./expand_pathnames/expand_pathnames.h"
#include "./remove_quoting/remove_quoting.h"
#include "./split_fields/split_fields.h"

static bool	expand_tildes_and_variables_for_all_arguments(
				t_list *arguments,
				t_program_vars *program_vars)
{
	t_list_node	*argument_node;

	argument_node = arguments->first;
	while (argument_node)
	{
		if (!expand_tildes((char **)&argument_node->value, program_vars))
			return (false);
		if (!expand_variables((char **)&argument_node->value, program_vars,
				NOT_HEREDOC))
			return (false);
		argument_node = argument_node->next;
	}
	return (true);
}

static bool	split_fields_for_all_arguments(
				t_list **arguments)
{
	t_list		*original_arguments;
	t_list_node	*argument_node;
	t_list		*split_arguments;
	t_list		*split_fields_from_argument;

	original_arguments = *arguments;
	split_arguments = ft_list_init();
	if (!split_arguments)
		return (false);
	argument_node = original_arguments->first;
	while (argument_node)
	{
		split_fields_from_argument = get_split_fields(argument_node->value);
		if (!split_fields_from_argument)
			return (ft_list_destroy(split_arguments, free), false);
		ft_list_merge(split_arguments, split_fields_from_argument);
		argument_node = argument_node->next;
	}
	*arguments = split_arguments;
	return (ft_list_destroy(original_arguments, free), true);
}

static bool	expand_pathnames_for_all_arguments(
				t_list **arguments)
{
	t_list		*original_arguments;
	t_list_node	*argument_node;
	t_list		*new_arguments;
	t_list		*expanded_paths_from_argument;

	original_arguments = *arguments;
	new_arguments = ft_list_init();
	if (!new_arguments)
		return (false);
	argument_node = original_arguments->first;
	while (argument_node)
	{
		expanded_paths_from_argument = get_expand_pathnames(argument_node->value);
		if (!expanded_paths_from_argument)
			return (ft_list_destroy(new_arguments, free), false);
		ft_list_merge(new_arguments, expanded_paths_from_argument);
		argument_node = argument_node->next;
	}
	*arguments = new_arguments;
	return (ft_list_destroy(original_arguments, free), true);
}

static void	remove_quoting_for_all_arguments(
				t_list *arguments)
{
	t_list_node	*argument_node;

	argument_node = arguments->first;
	while (argument_node)
	{
		remove_quoting(argument_node->value, NOT_HEREDOC);
		argument_node = argument_node->next;
	}
}

bool	expand_arguments(
			t_list **arguments,
			t_program_vars *program_vars)
{
	if (!expand_tildes_and_variables_for_all_arguments(*arguments,
			program_vars))
		return (false);
	split_fields_for_all_arguments(arguments);
	// pathname expansion - optional
	expand_pathnames_for_all_arguments(arguments);
	remove_quoting_for_all_arguments(*arguments);
	return (true);
}
