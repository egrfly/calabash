/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 21:28:10 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../interface/interface.h"
#include "../parse/parse.h"
#include "./execute.h"
#include "./execution_funcs/execution_funcs.h"

static const
	t_execution_func
	g_execution_funcs[] = {
[SIMPLE_COMMAND] = execute_simple_command,
[PIPE] = execute_pipeline,
[NEGATION] = execute_negation,
[AND] = execute_conditional_and,
[OR] = execute_conditional_or,
[SEQUENCE] = execute_sequence,
[GROUP] = execute_group,
[SUBSHELL] = execute_subshell,
};

int	execute_recursively(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	t_execution_func			execution_func;

	if (!node)
		return (SUCCESS);
	node_value = node->value;
	execution_func = g_execution_funcs[node_value->type];
	if (execution_func)
		return (execution_func(node, tokens_and_syntax_tree,
				program_name_and_env));
	return (SUCCESS);
}

int	execute(
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	return (execute_recursively(tokens_and_syntax_tree->syntax_tree->tree->root,
			tokens_and_syntax_tree, program_name_and_env));
}
