/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_standard_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:57:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/27 23:00:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"
#include "../../main.h"
#include "../interface.h"
#include "../input_processors/input_processors.h"
#include "../program_vars_lifecycle/program_vars_lifecycle.h"

int	handle_standard_input(int argc, char **argv, char **envp)
{
	t_program_vars	program_vars;
	int				exit_status;

	if (!init_program_vars(&program_vars, argc, argv, envp))
		return (GENERAL_FAILURE);
	if (!isatty(STDIN_FILENO))
		exit_status = process_noninteractive_file_input(STDIN_FILENO,
				&program_vars);
	else
		exit_status = process_interactive_input(&program_vars);
	destroy_program_vars(&program_vars);
	return (exit_status);
}
