/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:37:03 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 06:05:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../parse/parse.h"
#include "../execute.h"

int	builtin_unset(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	t_list_node					*current_env_node;
	size_t						argument_length;
	size_t						identifier_length;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (ft_strstarts(argument_node->value, "-")
		&& ft_strlen(argument_node->value) > 1
		&& ft_strcmp(argument_node->value, "--"))
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
				program_name_and_env->name, node_value->arguments->first->value,
				"options not supported"), GENERAL_FAILURE);
	if (!ft_strcmp(argument_node->value, "--"))
		argument_node = argument_node->next;
	while (argument_node)
	{
		argument_length = ft_strlen(argument_node->value);
		current_env_node = program_name_and_env->env->first;
		while (current_env_node)
		{
			identifier_length = ft_strcspn(current_env_node->value, "=");
			if (argument_length == identifier_length
				&& !ft_strncmp(argument_node->value, current_env_node->value,
					identifier_length))
			{
				ft_list_removenode(program_name_and_env->env, current_env_node);
				ft_list_delnode(current_env_node, free);
			}
			current_env_node = current_env_node->next;
		}
		argument_node = argument_node->next;
	}
	return (SUCCESS);
}
