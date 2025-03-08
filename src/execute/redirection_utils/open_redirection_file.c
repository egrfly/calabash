/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 05:16:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 05:23:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../redirection_utils/redirection_utils.h"

bool	open_redirection_file(
			int *fd,
			char *file_name,
			int mode,
			char *program_name)
{
	*fd = open(file_name, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*fd == OPEN_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name,
				file_name, strerror(errno)), false);
	return (true);
}
