/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_read_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 07:29:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_read_redirection(
			t_redirection *redirection,
			char *program_name)
{
	int	left_fd;
	int	right_fd;

	if (redirection->left_type == REDIRECTION_LEFT_NUMBER)
		left_fd = redirection->left_content.number;
	else
		left_fd = STDIN_FILENO;
	if (!open_redirection_file(&right_fd, redirection->right_content.word,
			O_RDONLY, program_name))
		return (false);
	register_redirection_reset_instruction(
		&redirection->primary_reset_instruction, left_fd);
	dup2(right_fd, left_fd);
	return (close(right_fd), true);
}
