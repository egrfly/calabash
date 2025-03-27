/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:10:03 by aistok            #+#    #+#             */
/*   Updated: 2025/03/18 01:19:51 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_ctype.h"
#include "ft_list.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"

#define TOO_MANY_ARGUMENTS 1
#define NUMERIC_ARGUMENT_REQUIRED 2

static bool	handle_exit_options(
				t_list_node **argument_node)
{
	if (*argument_node
		&& ft_strstarts((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "--")
		&& !ft_strall(&((char *)(*argument_node)->value)[1], ft_isdigit))
		return (false);
	if (*argument_node
		&& !ft_strcmp((*argument_node)->value, "--"))
		*argument_node = (*argument_node)->next;
	return (true);
}

int	builtin_exit(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	long						exit_status;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!handle_exit_options(&argument_node))
		return (ft_dprintf(STDERR_FILENO, "%s: exit: options not supported\n",
				get_program_name()), GENERAL_FAILURE);
	exit_status = program_vars->last_exit_status;
	if (argument_node && !ft_strtol(argument_node->value, &exit_status))
		return (ft_dprintf(STDERR_FILENO,
				"%s: exit: numeric argument required\n",
				get_program_name()), NUMERIC_ARGUMENT_REQUIRED);
	else if (argument_node && argument_node->next)
		return (ft_dprintf(STDERR_FILENO, "%s: exit: too many arguments\n",
				get_program_name()), TOO_MANY_ARGUMENTS);
	else
	{
		program_vars->should_exit = true;
		return (exit_status);
	}
}
