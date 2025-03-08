/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_output_duplication.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 08:17:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"
#include "./redirection_funcs.h"

bool	perform_output_duplication(
			t_redirection *redirection,
			char *program_name)
{
	int	left_fd;
	int	right_fd;

	if (redirection->right_type == REDIRECTION_RIGHT_WORD
		&& redirection->left_type == NO_REDIRECTION_LEFT_CONTENT)
		return (perform_write_both_redirection(redirection, program_name));
	if (redirection->right_type == REDIRECTION_RIGHT_WORD)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
				program_name, redirection->right_content.word), false);
	if (redirection->left_type == REDIRECTION_LEFT_NUMBER)
		left_fd = redirection->left_content.number;
	else
		left_fd = STDOUT_FILENO;
	if (redirection->right_type == REDIRECTION_RIGHT_DASH)
		return (close(left_fd), true);
	right_fd = redirection->right_content.number;
	register_redirection_reset_instruction(
		&redirection->primary_reset_instruction, left_fd);
	if (dup2(right_fd, left_fd) == DUP_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: %d: %s\n", program_name,
				redirection->right_content.number, strerror(errno)), false);
	if (redirection->right_type == REDIRECTION_RIGHT_NUMBER_DASH)
		close(right_fd);
	return (true);
}
