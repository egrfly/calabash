/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/11 00:59:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/option_utils/option_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../execution_funcs/execution_funcs.h"

static bool	handle_echo_options(
				t_list_node **argument_node,
				bool *print_last_newline)
{
	while (*argument_node
		&& is_option_sequence_consisting_of_chars(
			(*argument_node)->value, "n"))
	{
		*print_last_newline = false;
		*argument_node = (*argument_node)->next;
	}
	if (*argument_node
		&& is_option_sequence_consisting_of_chars(
			(*argument_node)->value, "neE"))
		return (false);
	if (*argument_node
		&& !ft_strcmp((*argument_node)->value, "--"))
		*argument_node = (*argument_node)->next;
	return (true);
}

int	builtin_echo(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	bool						print_last_newline;

	(void)tokens_and_syntax_tree;
	(void)program_vars;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	print_last_newline = true;
	if (!handle_echo_options(&argument_node, &print_last_newline))
		return (ft_dprintf(STDERR_FILENO, "%s: echo: %s\n", get_program_name(),
				"options other than -n not supported"), GENERAL_FAILURE);
	while (argument_node)
	{
		if (ft_printf("%s", argument_node->value) == WRITE_FAILURE)
			return (ft_dprintf(STDERR_FILENO, "%s: echo: %s\n",
					get_program_name(), strerror(errno)), GENERAL_FAILURE);
		if (argument_node->next)
			ft_printf(" ");
		argument_node = argument_node->next;
	}
	if (print_last_newline && ft_printf("\n") == WRITE_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: echo: %s\n",
				get_program_name(), strerror(errno)), GENERAL_FAILURE);
	return (SUCCESS);
}
