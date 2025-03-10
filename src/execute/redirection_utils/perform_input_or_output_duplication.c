/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_input_or_output_duplication.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:10:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 11:00:33 by emflynn          ###   ########.fr       */
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
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_input_or_output_duplication(
			t_redirection *redirection,
			int fallback_left_fd)
{
	int	left_fd;
	int	right_fd;

	if (redirection->right_type == REDIRECTION_RIGHT_WORD)
		return (ft_dprintf(STDERR_FILENO, "%s: %s: ambiguous redirect\n",
				get_program_name(), redirection->right_content.word), false);
	if (redirection->left_type == REDIRECTION_LEFT_NUMBER)
		left_fd = redirection->left_content.number;
	else
		left_fd = fallback_left_fd;
	register_redirection_reset_instruction(
		&redirection->primary_reset_instruction, left_fd);
	if (redirection->right_type == REDIRECTION_RIGHT_DASH)
		return (close(left_fd), true);
	right_fd = redirection->right_content.number;
	if (dup2(right_fd, left_fd) == DUP_FAILURE)
		return (ft_dprintf(STDERR_FILENO, "%s: %d: %s\n", get_program_name(),
				redirection->right_content.number, strerror(errno)), false);
	if (redirection->right_type == REDIRECTION_RIGHT_NUMBER_DASH)
	{
		register_redirection_reset_instruction(
			&redirection->primary_reset_instruction, right_fd);
		close(right_fd);
	}
	return (true);
}
