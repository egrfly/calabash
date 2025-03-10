/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:14:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 14:55:25 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../var_utils/var_utils.h"

static bool	handle_env_arguments(
				t_list_node *argument_node)
{
	if (argument_node
		&& ft_strstarts(argument_node->value, "-")
		&& ft_strcmp(argument_node->value, "-")
		&& ft_strcmp(argument_node->value, "--"))
		return (false);
	if (argument_node
		&& !ft_strcmp(argument_node->value, "--"))
		argument_node = argument_node->next;
	if (argument_node)
		return (false);
	return (true);
}

int	builtin_env(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	t_list_node					*current_var_node;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!handle_env_arguments(argument_node))
		return (ft_dprintf(STDERR_FILENO, "%s: env: %s\n",
				get_program_name(), "options/arguments not supported"),
			GENERAL_FAILURE);
	current_var_node = program_vars->vars->first;
	while (current_var_node)
	{
		if (!ft_strstarts(current_var_node->value, NOT_EXPORTED_PREFIX)
			&& ft_strchr(current_var_node->value, '='))
			ft_printf("%s\n", current_var_node->value);
		current_var_node = current_var_node->next;
	}
	return (SUCCESS);
}
