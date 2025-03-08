/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:42:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:02:19 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_stdio.h"
#include "../../main.h"
#include "../interface.h"
#include "../input_processors/input_processors.h"
#include "../option_utils/option_utils.h"
#include "../program_name_utils/program_name_utils.h"
#include "../program_vars_lifecycle/program_vars_lifecycle.h"

int	handle_c_option(char **argv, char **envp, int option_count)
{
	t_program_vars	program_vars;
	char			*program_argument;
	int				exit_status;

	if (!init_program_vars(&program_vars, envp))
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), GENERAL_FAILURE);
	program_argument = argv[1 + option_count];
	if (!program_argument)
	{
		destroy_program_vars(&program_vars);
		return (ft_dprintf(STDERR_FILENO,
				"%s: -c: option requires an argument\n",
				get_program_name()), INCORRECT_USAGE);
	}
	exit_status = process_noninteractive_string_input(program_argument,
			&program_vars);
	destroy_program_vars(&program_vars);
	return (exit_status);
}
