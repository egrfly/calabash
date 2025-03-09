/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:40:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 01:39:39 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "ft_list.h"
# include "../../interface/interface.h"
# include "../execute.h"

typedef struct s_exec_params
{
	char	*command;
	char	*path;
	char	**args;
	char	**envp;
}	t_exec_params;

bool	init_exec_params(
			t_exec_params *exec_params,
			t_list *arguments,
			t_list *assignments,
			t_list *env);
void	destroy_exec_params(
			t_exec_params *exec_params);
void	exit_due_to_lack_of_memory(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements);
void	exit_due_to_redirection_failure(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements);
void	exit_due_to_unfound_command(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements,
			t_list *redirections);
void	exit_due_to_execve_failure(
			t_program_vars *program_vars,
			t_exec_params *exec_params,
			t_fixed_program_elements *fixed_program_elements,
			t_list *redirections);

#endif
