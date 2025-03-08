/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_read_or_write_redirection.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:00:40 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:05:01 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_read_or_write_redirection(
			t_redirection *redirection,
			int mode,
			int fallback_left_fd,
			bool is_here_doc)
{
	int	left_fd;
	int	right_fd;

	if (redirection->left_type == REDIRECTION_LEFT_NUMBER)
		left_fd = redirection->left_content.number;
	else
		left_fd = fallback_left_fd;
	if (!open_redirection_file(&right_fd, redirection->right_content.word,
			mode, is_here_doc))
		return (false);
	register_redirection_reset_instruction(
		&redirection->primary_reset_instruction, left_fd);
	dup2(right_fd, left_fd);
	close(right_fd);
	if (is_here_doc)
		unlink(redirection->right_content.word);
	return (true);
}
