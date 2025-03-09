/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_due_to_execve_failure.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:52:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 01:38:32 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
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

void	exit_due_to_execve_failure(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements,
			t_list *redirections)
{
	int	exit_status;

	if (errno == ENOENT)
		exit_status = NOT_FOUND;
	else if (errno == EACCES)
		exit_status = COULD_NOT_EXECUTE;
	else
		exit_status = GENERAL_FAILURE;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", get_program_name(),
		exec_params->command, strerror(errno));
	revert_redirections(redirections);
	destroy_program_vars(program_vars);
	destroy_exec_params(exec_params);
	destroy_fixed_program_elements(fixed_program_elements);
	exit(exit_status);
}
