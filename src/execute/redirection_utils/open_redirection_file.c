/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 05:16:57 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:58:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../redirection_utils/redirection_utils.h"

bool	open_redirection_file(
			int *fd,
			char *file_name,
			int mode,
			bool is_here_doc)
{
	*fd = open(file_name, mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*fd == OPEN_FAILURE)
	{
		if (is_here_doc)
		{
			unlink(file_name);
			return (ft_dprintf(STDERR_FILENO, "%s: here-document failure\n",
					get_program_name()), false);
		}
		else
			return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
					get_program_name(), file_name, strerror(errno)), false);
	}
	return (true);
}
