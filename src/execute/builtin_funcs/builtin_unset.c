/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:37:03 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 14:20:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../var_utils/var_utils.h"

static bool	handle_unset_options(
				t_list_node **argument_node)
{
	if (*argument_node
		&& ft_strstarts((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "--"))
		return (false);
	if (argument_node
		&& !ft_strcmp((*argument_node)->value, "--"))
		*argument_node = (*argument_node)->next;
	return (true);
}

int	builtin_unset(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!handle_unset_options(&argument_node))
		return (ft_dprintf(STDERR_FILENO, "%s: unset: %s\n",
				get_program_name(), "options not supported"),
			GENERAL_FAILURE);
	while (argument_node)
	{
		remove_var(argument_node->value, program_vars->vars);
		argument_node = argument_node->next;
	}
	return (SUCCESS);
}
