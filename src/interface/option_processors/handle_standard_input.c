/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_standard_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:57:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:02:32 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../interface.h"
#include "../input_processors/input_processors.h"
#include "../program_name_utils/program_name_utils.h"
#include "../program_vars_lifecycle/program_vars_lifecycle.h"

int	handle_standard_input(char **envp)
{
	t_program_vars	program_vars;
	int				exit_status;

	if (!init_program_vars(&program_vars, envp))
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), GENERAL_FAILURE);
	if (!isatty(STDIN_FILENO))
		exit_status = process_noninteractive_file_input(STDIN_FILENO,
				&program_vars);
	else
		exit_status = process_interactive_input(&program_vars);
	destroy_program_vars(&program_vars);
	return (exit_status);
}
