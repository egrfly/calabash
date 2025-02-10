/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_external_input_file.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 22:39:44 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/10 22:41:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../input_processors/input_processors.h"
#include "../interface.h"

int	handle_external_input_file(char **argv,
		int options_end_count)
{
	int	input_file_fd;
	int	return_value;

	input_file_fd = open(argv[1 + options_end_count], O_RDONLY);
	if (input_file_fd > -1)
	{
		return_value
			= process_noninteractive_file_input(input_file_fd, argv[0]);
		close(input_file_fd);
		return (return_value);
	}
	if (errno == ENOENT)
		return_value = NOT_FOUND;
	else
		return_value = COULD_NOT_EXECUTE;
	return (ft_dprintf(STDERR_FILENO,
			"%s: %s: %s\n",
			argv[0], argv[1 + options_end_count],
			strerror(errno)), return_value);
}
