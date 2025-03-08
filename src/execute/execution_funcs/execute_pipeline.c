/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:57:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 15:57:25 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "../pipeline_lifecycle/pipeline_lifecycle.h"
#include "../pipeline_utils/pipeline_utils.h"

static t_binary_tree_node	*select_correct_child_to_execute(
								t_binary_tree_node *node,
								bool is_last_in_pipeline)
{
	if (is_last_in_pipeline)
		return (node->primary_child);
	else
		return (node->secondary_child);
}

static bool	execute_section_of_pipeline(
				t_pipeline *pipeline,
				t_program_vars *program_vars,
				t_binary_tree_node *node,
				t_fixed_program_elements *fixed_program_elements)
{
	int	exit_status;

	pipeline->pids[pipeline->current_index] = fork();
	if (pipeline->pids[pipeline->current_index] == FORK_FAILURE)
		return (close_pipe_fds_for_process(pipeline->pipe_fds,
				pipeline->pipe_count), false);
	else if (pipeline->pids[pipeline->current_index] == CHILD_PROCESS_ID)
	{
		fixed_program_elements->active_pipeline = pipeline;
		reroute_standard_input_if_necessary(pipeline);
		reroute_standard_output_if_necessary(pipeline);
		close_pipe_fds_for_process(pipeline->pipe_fds, pipeline->pipe_count);
		exit_status = execute_recursively(select_correct_child_to_execute(node,
					pipeline->current_index == pipeline->pipe_count),
				fixed_program_elements, program_vars);
		destroy_pipeline(pipeline);
		destroy_fixed_program_elements(fixed_program_elements);
		exit(exit_status);
	}
	return (true);
}

// TODO: look into macros like WIFEXITED, WEXITSTATUS, WIFSIGNALED etc.
// TODO: check if exit status is random based on order of waiting
int	execute_pipeline(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars)
{
	int					exit_status;
	t_pipeline			pipeline;

	exit_status = init_pipeline(&pipeline,
			count_pipes_in_current_pipeline(node));
	if (exit_status != SUCCESS)
		return (exit_status);
	pipeline.current_index = 0;
	while (pipeline.current_index <= pipeline.pipe_count)
	{
		if (!execute_section_of_pipeline(&pipeline,
				program_vars, node, fixed_program_elements))
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", get_program_name(),
				"cannot fork", strerror(errno));
			return (destroy_pipeline(&pipeline), GENERAL_FAILURE);
		}
		pipeline.current_index++;
		if (pipeline.current_index < pipeline.pipe_count)
			node = node->primary_child;
	}
	close_pipe_fds_for_process(pipeline.pipe_fds, pipeline.pipe_count);
	while (wait(&exit_status) > 0)
		;
	return (destroy_pipeline(&pipeline), exit_status);
}
