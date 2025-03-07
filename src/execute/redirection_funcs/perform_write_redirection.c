/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_write_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 10:03:40 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../parse/parse.h"
#include "./redirection_funcs.h"

int	perform_write_redirection(
		t_redirection *redirection,
		char *program_name)
{
	int	src_fd;
	int	dest_fd;
	int	original_src_fd;

	if (redirection->left_type == REDIRECTION_LEFT_NUMBER)
		src_fd = redirection->left_content.number;
	else
		src_fd = STDOUT_FILENO;
	dest_fd = open(redirection->right_content.word,
			O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (dest_fd == OPEN_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name,
				redirection->right_content.word, strerror(errno)),
			GENERAL_FAILURE);
	original_src_fd = dup(src_fd);
	if (original_src_fd != DUP_FAILURE)
	{
		redirection->primary_reset_instruction.is_active = true;
		redirection->primary_reset_instruction.original_fd = original_src_fd;
		redirection->primary_reset_instruction.fd_to_reset = src_fd;
	}
	dup2(dest_fd, src_fd);
	close(dest_fd);
	return (SUCCESS);
}
