/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/16 15:06:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/option_utils/option_utils.h"
#include "../../interface/command_history_utils/command_history_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"

static void	show_history_command_usage(void)
{
	ft_dprintf(STDERR_FILENO,
		"%s: history: supported usage: history -c\n", get_program_name());
	ft_dprintf(STDERR_FILENO,
		"Options:\n");
	ft_dprintf(STDERR_FILENO,
		"  -c\t(mandatory) clear the command history list\n");
}

int	builtin_history(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;

	(void)tokens_and_syntax_tree;
	(void)program_vars;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (!argument_node
		|| !is_option_sequence_consisting_of_chars(argument_node->value, "c"))
	{
		show_history_command_usage();
		return (INCORRECT_USAGE);
	}
	clear_command_history();
	return (SUCCESS);
}
