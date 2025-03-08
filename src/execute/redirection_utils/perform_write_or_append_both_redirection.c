/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_write_or_append_both_redirection.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:57:52 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 14:58:52 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_write_or_append_both_redirection(
			t_redirection *redirection,
			int truncate_or_append)
{
	int	right_fd;

	if (!open_redirection_file(&right_fd, redirection->right_content.word,
			O_WRONLY | O_CREAT | truncate_or_append, NOT_HERE_DOC))
		return (false);
	register_redirection_reset_instruction(
		&redirection->primary_reset_instruction, STDOUT_FILENO);
	register_redirection_reset_instruction(
		&redirection->secondary_reset_instruction, STDERR_FILENO);
	dup2(right_fd, STDOUT_FILENO);
	dup2(right_fd, STDERR_FILENO);
	return (close(right_fd), true);
}
