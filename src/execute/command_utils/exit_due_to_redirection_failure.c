/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_due_to_redirection_failure.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:52:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:01:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "./command_utils.h"

void	exit_due_to_redirection_failure(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements)
{
	destroy_program_vars(program_vars);
	destroy_exec_params(exec_params);
	destroy_fixed_program_elements(fixed_program_elements);
	exit(GENERAL_FAILURE);
}
