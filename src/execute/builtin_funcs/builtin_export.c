/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:22:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 06:11:35 by emflynn          ###   ########.fr       */
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
#include "../../parse/word_utils/word_utils.h"
#include "../execute.h"
#include "../builtin_utils/builtin_utils.h"

int	builtin_export(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	int							exit_status;
	t_list_node					*argument_node;
	char						*assignment;
	size_t						identifier_length;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	if (node_value->arguments->size == 1)
	{
		// TODO: print exported values
		return (SUCCESS);
	}
	argument_node = node_value->arguments->first->next;
	if (ft_strstarts(argument_node->value, "-")
		&& ft_strlen(argument_node->value) > 1
		&& ft_strcmp(argument_node->value, "--"))
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
				program_name_and_env->name, node_value->arguments->first->value,
				"options not supported"), GENERAL_FAILURE);
	if (!ft_strcmp(argument_node->value, "--"))
		argument_node = argument_node->next;
	exit_status = SUCCESS;
	argument_node = node_value->arguments->first->next;
	while (argument_node)
	{
		identifier_length = ft_strcspn(argument_node->value, "=");
		if (range_is_identifier(argument_node->value, START, identifier_length))
		{
			// TODO: remember to unset variable with same key if exists first!
			assignment = ft_strdup(argument_node->value);
			if (!assignment
				|| !ft_list_append(program_name_and_env->env, assignment))
			{
				free(assignment);
				return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
						program_name_and_env->name), GENERAL_FAILURE);
			}
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: `%s': %s\n",
				program_name_and_env->name, node_value->arguments->first->value,
				argument_node->value, "not a valid identifier");
			exit_status = GENERAL_FAILURE;
		}
		argument_node = argument_node->next;
	}
	return (exit_status);
}
