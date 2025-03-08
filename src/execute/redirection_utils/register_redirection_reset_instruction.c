/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_redirection_reset_instruction.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 21:08:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 21:16:22 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "../../parse/parse.h"
#include "./redirection_utils.h"

void	register_redirection_reset_instruction(
			t_redirection_reset_instruction *reset_instruction,
			int fd_to_reset)
{
	int	original_fd;

	original_fd = dup(fd_to_reset);
	if (original_fd != DUP_FAILURE)
	{
		reset_instruction->is_active = true;
		reset_instruction->original_fd = original_fd;
		reset_instruction->fd_to_reset = fd_to_reset;
	}
}
