/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_append_both_redirection.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:23:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 07:28:57 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "../../parse/parse.h"
#include "../redirection_utils/redirection_utils.h"

bool	perform_append_both_redirection(
			t_redirection *redirection,
			char *program_name)
{
	int	right_fd;

	if (!open_redirection_file(&right_fd, redirection->right_content.word,
			O_WRONLY | O_CREAT | O_APPEND, program_name))
		return (false);
	register_redirection_reset_instruction(
		&redirection->primary_reset_instruction, STDOUT_FILENO);
	register_redirection_reset_instruction(
		&redirection->secondary_reset_instruction, STDERR_FILENO);
	dup2(right_fd, STDOUT_FILENO);
	dup2(right_fd, STDERR_FILENO);
	return (close(right_fd), true);
}
