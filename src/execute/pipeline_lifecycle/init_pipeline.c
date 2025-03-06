/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 01:57:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 17:25:21 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "../../interface/interface.h"
#include "../pipeline_utils/pipeline_utils.h"
#include "./pipeline_lifecycle.h"

int	init_pipeline(
		t_pipeline *pipeline,
		int pipe_count,
		char *program_name)
{
	pipeline->pipe_count = pipe_count;
	pipeline->pipe_fds = ft_calloc(1, sizeof(int [pipeline->pipe_count][2]));
	pipeline->pids = ft_calloc(pipeline->pipe_count + 1, sizeof(int));
	if (!pipeline->pipe_fds || !pipeline->pids)
	{
		destroy_pipeline(pipeline);
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				program_name), GENERAL_FAILURE);
	}
	pipeline->current_index = 0;
	while (pipeline->current_index < pipeline->pipe_count)
	{
		if (pipe(pipeline->pipe_fds[pipeline->current_index]) == PIPE_FAILURE)
		{
			close_pipe_fds_for_process(pipeline->pipe_fds,
				pipeline->current_index);
			destroy_pipeline(pipeline);
			return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n",
					program_name, "cannot make pipe",
					strerror(errno), GENERAL_FAILURE));
		}
		pipeline->current_index++;
	}
	return (SUCCESS);
}
