/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_due_to_unfound_command.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:50:27 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:03:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "./command_utils.h"

void	exit_due_to_unfound_command(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: command not found\n", get_program_name(),
		exec_params->command);
	destroy_program_vars(program_vars);
	destroy_exec_params(exec_params);
	destroy_fixed_program_elements(fixed_program_elements);
	exit(NOT_FOUND);
}
