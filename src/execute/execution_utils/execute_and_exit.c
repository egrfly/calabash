/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:11:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 15:12:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../interface/interface.h"
#include "../../interface/command_history_utils/command_history_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../execute.h"
#include "./execution_utils.h"

void	execute_and_exit(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_program_vars *program_vars)
{
	int	exit_status;

	exit_status = execution_func(node, tokens_and_syntax_tree, program_vars);
	destroy_program_vars(program_vars);
	destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
	clear_command_history();
	exit(exit_status);
}
