/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_due_to_unfound_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:50:27 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 07:42:26 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "./command_utils.h"

void	exit_due_to_unfound_command(
			char *program_name,
			t_exec_params *exec_params,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: command not found\n", program_name,
		exec_params->command);
	destroy_exec_params(exec_params);
	destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
	exit(NOT_FOUND);
}
