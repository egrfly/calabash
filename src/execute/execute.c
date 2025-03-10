/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 15:35:17 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_binary_tree.h"
#include "../main.h"
#include "../interface/interface.h"
#include "../parse/parse.h"
#include "./execute.h"
#include "./execution_funcs/execution_funcs.h"

static const
	t_execution_func
	g_execution_funcs[] = {
[SIMPLE_COMMAND] = execute_simple_command,
[GROUP] = execute_group,
[SUBSHELL] = execute_subshell,
[WHILE_COMMAND] = NULL,
[UNTIL_COMMAND] = NULL,
[IF_COMMAND] = NULL,
[FOR_COMMAND] = NULL,
[SELECT_COMMAND] = NULL,
[CASE_COMMAND] = NULL,
[FUNCTION] = NULL,
[PIPE] = execute_pipeline,
[PIPE_BOTH] = execute_pipeline,
[TIME_COMMAND] = NULL,
[NEGATION] = execute_negation,
[OR] = execute_conditional_or,
[AND] = execute_conditional_and,
[SEQUENCE] = execute_sequence,
[BACKGROUND] = NULL,
[COPROCESS] = NULL,
};

int	execute_recursively(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_execution_func			execution_func;

	if (!node)
		return (SUCCESS);
	node_value = node->value;
	execution_func = g_execution_funcs[node_value->type];
	if (execution_func)
		return (execution_func(node, tokens_and_syntax_tree,
				program_vars));
	return (SUCCESS);
}

int	execute(
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	return (execute_recursively(tokens_and_syntax_tree->syntax_tree->tree->root,
			tokens_and_syntax_tree, program_vars));
}
