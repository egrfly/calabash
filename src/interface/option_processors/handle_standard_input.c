/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_standard_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:57:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 19:22:15 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"
#include "ft_stdio.h"
#include "../interface.h"
#include "../env_utils/env_utils.h"
#include "../input_processors/input_processors.h"

int	handle_standard_input(char **argv, char **envp)
{
	t_program_name_and_env	program_name_and_env;
	int						exit_status;

	program_name_and_env.name = argv[0];
	program_name_and_env.env = get_env_list_from_envp(envp);
	if (!program_name_and_env.env)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				program_name_and_env.name), GENERAL_FAILURE);
	if (!isatty(STDIN_FILENO))
		exit_status = process_noninteractive_file_input(STDIN_FILENO,
				&program_name_and_env);
	else
		exit_status = process_interactive_input(&program_name_and_env);
	ft_list_destroy(program_name_and_env.env, free);
	return (exit_status);
}
