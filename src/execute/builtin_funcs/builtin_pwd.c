/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/11 00:59:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../execute.h"
#include "../execution_funcs/execution_funcs.h"

static bool	handle_echo_options(
				t_list_node *argument_node)
{
	return (!argument_node
		|| !ft_strstarts(argument_node->value, "-")
		|| !ft_strcmp(argument_node->value, "-")
		|| !ft_strcmp(argument_node->value, "--"));
}

int	builtin_pwd(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	char						*path;

	(void)tokens_and_syntax_tree;
	(void)program_vars;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!handle_echo_options(argument_node))
		return (ft_dprintf(STDERR_FILENO, "%s: pwd: %s\n", get_program_name(),
				"options not supported"), GENERAL_FAILURE);
	path = getcwd(NULL, 0);
	if (!path)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), GENERAL_FAILURE);
	ft_printf("%s\n", path);
	return (free(path), SUCCESS);
}
