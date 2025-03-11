/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/11 00:59:29 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"

static bool	is_dash_c_sequence(const char *argument)
{
	size_t	i;

	if (ft_strstarts(argument, "-c"))
	{
		i = ft_strlen("-c");
		while (argument[i] && argument[i] == 'c')
			i++;
		if (!argument[i])
			return (true);
	}
	return (false);
}

static void	show_history_command_usage(void)
{
	ft_printf("%s: history: supported usage: history -c\n", get_program_name());
	ft_printf("Options:\n");
	ft_printf("  -c\t(mandatory) clear the command history list\n");
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
	if (!argument_node || !is_dash_c_sequence(argument_node->value))
	{
		show_history_command_usage();
		return (INCORRECT_USAGE);
	}
	rl_clear_history();
	ft_printf("Command history list now cleared.\n");
	return (SUCCESS);
}
