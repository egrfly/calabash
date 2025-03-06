/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_external_input_file.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:39:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 20:44:49 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../interface.h"
#include "../env_utils/env_utils.h"
#include "../input_processors/input_processors.h"

int	handle_external_input_file(char **argv, char **envp,
		int options_end_count)
{
	t_program_name_and_env	program_name_and_env;
	int						input_file_fd;
	int						exit_status;

	program_name_and_env.name = argv[0];
	program_name_and_env.env = get_env_list_from_envp(envp);
	if (!program_name_and_env.env)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				program_name_and_env.name), GENERAL_FAILURE);
	input_file_fd = open(argv[1 + options_end_count], O_RDONLY);
	if (input_file_fd > -1)
	{
		exit_status = process_noninteractive_file_input(
				input_file_fd, &program_name_and_env);
		close(input_file_fd);
		return (ft_list_destroy(program_name_and_env.env, free), exit_status);
	}
	if (errno == ENOENT)
		exit_status = NOT_FOUND;
	else
		exit_status = COULD_NOT_EXECUTE;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name_and_env.name,
		argv[1 + options_end_count], strerror(errno));
	return (ft_list_destroy(program_name_and_env.env, free), exit_status);
}
