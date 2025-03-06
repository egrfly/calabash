/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:14:24 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 05:46:08 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../interface/interface.h"
#include "../../parse/parse.h"
#include "../execute.h"

int	builtin_env(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*current_env_node;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	if (node_value->arguments->size > 1
		&& !ft_strcmp(node_value->arguments->first->next->value, "--"))
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
				program_name_and_env->name, node_value->arguments->first->value,
				"options/arguments not supported"), GENERAL_FAILURE);
	current_env_node = program_name_and_env->env->first;
	while (current_env_node)
	{
		ft_printf("%s\n", current_env_node->value);
		current_env_node = current_env_node->next;
	}
	return (SUCCESS);
}
