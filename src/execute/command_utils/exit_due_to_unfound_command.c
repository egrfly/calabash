/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_due_to_unfound_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:50:27 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 05:57:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "../redirection_utils/redirection_utils.h"
#include "./command_utils.h"

void	exit_due_to_unfound_command(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_list *redirections)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: command not found\n", get_program_name(),
		exec_params->command);
	revert_redirections(redirections);
	destroy_program_vars(program_vars);
	destroy_exec_params(exec_params);
	destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
	exit(NOT_FOUND);
}
