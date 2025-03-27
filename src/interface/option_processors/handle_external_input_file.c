/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_external_input_file.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:39:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/22 10:52:27 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../main.h"
#include "../interface.h"
#include "../input_processors/input_processors.h"
#include "../program_property_utils/program_property_utils.h"
#include "../program_vars_lifecycle/program_vars_lifecycle.h"

int	handle_external_input_file(int argc, char **argv, char **envp,
		int options_end_count)
{
	t_program_vars	program_vars;
	int				input_file_fd;
	int				exit_status;

	if (!init_program_vars(&program_vars, argc, argv, envp))
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), GENERAL_FAILURE);
	input_file_fd = open(argv[1 + options_end_count], O_RDONLY);
	if (input_file_fd > -1)
	{
		exit_status = process_noninteractive_file_input(
				input_file_fd, &program_vars);
		close(input_file_fd);
		return (destroy_program_vars(&program_vars), exit_status);
	}
	if (errno == ENOENT)
		exit_status = NOT_FOUND;
	else
		exit_status = COULD_NOT_EXECUTE;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", get_program_name(),
		argv[1 + options_end_count], strerror(errno));
	return (destroy_program_vars(&program_vars), exit_status);
}
