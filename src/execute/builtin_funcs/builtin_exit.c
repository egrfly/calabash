/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:10:03 by aistok            #+#    #+#             */
/*   Updated: 2025/03/11 02:06:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdlib.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"

#define TOO_MANY_ARGUMENTS 1
#define NUMERIC_ARGUMENT_REQUIRED 2

int	builtin_exit(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	long						exit_code;

	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	exit_code = SUCCESS;
	if (argument_node && !ft_strtol(argument_node->value, &exit_code))
		return (ft_dprintf(STDERR_FILENO,
				"%s: exit: numeric argument required\n",
				get_program_name()), NUMERIC_ARGUMENT_REQUIRED);
	else if (argument_node && argument_node->next)
		return (ft_dprintf(STDERR_FILENO, "%s: exit: too many arguments\n",
				get_program_name()), TOO_MANY_ARGUMENTS);
	else
	{
		ft_printf("exit\n");
		destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
		destroy_program_vars(program_vars);
		exit(exit_code);
	}
}
