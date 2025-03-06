/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe_fds_for_process.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 02:02:35 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 02:03:30 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./pipeline_utils.h"

void	close_pipe_fds_for_process(
			int (*pipe_fds)[2],
			int pipe_count)
{
	int	current_index;

	current_index = 0;
	while (current_index < pipe_count)
	{
		close(pipe_fds[current_index][READ_END]);
		close(pipe_fds[current_index][WRITE_END]);
		current_index++;
	}
}
