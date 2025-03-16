/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:57:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/16 15:14:56 by emflynn          ###   ########.fr       */
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
#include "../../interface/command_history_utils/command_history_utils.h"
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../interface/program_vars_lifecycle/program_vars_lifecycle.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "../pipeline_lifecycle/pipeline_lifecycle.h"
#include "../pipeline_utils/pipeline_utils.h"

static t_binary_tree_node	*select_correct_child_to_execute(
								t_binary_tree_node *node,
								bool is_first_in_pipeline)
{
	if (is_first_in_pipeline)
		return (node->primary_child);
	else
		return (node->secondary_child);
}

static bool	execute_section_of_pipeline(
				t_pipeline *pipeline,
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree,
				t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	int							exit_status;

	pipeline->pids[pipeline->current_index] = fork();
	if (pipeline->pids[pipeline->current_index] == FORK_FAILURE)
		return (close_pipe_fds_for_process(pipeline->pipe_fds,
				pipeline->pipe_count), false);
	else if (pipeline->pids[pipeline->current_index] == CHILD_PROCESS_ID)
	{
		program_vars->active_pipeline = pipeline;
		node_value = node->value;
		reroute_standard_input_if_necessary(pipeline);
		reroute_standard_output_if_necessary(pipeline);
		if (node_value->type == PIPE_BOTH)
			reroute_standard_error_if_necessary(pipeline);
		close_pipe_fds_for_process(pipeline->pipe_fds, pipeline->pipe_count);
		exit_status = execute_recursively(select_correct_child_to_execute(node,
					pipeline->current_index == 0), tokens_and_syntax_tree,
				program_vars);
		destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
		destroy_program_vars(program_vars);
		clear_command_history();
		exit(exit_status);
	}
	return (true);
}

static void	wait_for_all_child_processes(
				t_pipeline *pipeline,
				int *exit_status)
{
	waitpid(pipeline->pids[pipeline->pipe_count], exit_status, NO_OPTIONS);
	while (wait(NO_ARG) > 0)
		;
}

int	execute_pipeline(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	int			exit_status;
	t_pipeline	pipeline;

	exit_status = init_pipeline(&pipeline,
			count_pipes_in_current_pipeline(node));
	if (exit_status != SUCCESS)
		return (exit_status);
	pipeline.current_index = pipeline.pipe_count;
	while (pipeline.current_index >= 0)
	{
		if (!execute_section_of_pipeline(&pipeline,
				node, tokens_and_syntax_tree, program_vars))
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", get_program_name(),
				"cannot fork", strerror(errno));
			return (destroy_pipeline(&pipeline), GENERAL_FAILURE);
		}
		pipeline.current_index--;
		if (pipeline.current_index > 0)
			node = node->primary_child;
	}
	close_pipe_fds_for_process(pipeline.pipe_fds, pipeline.pipe_count);
	wait_for_all_child_processes(&pipeline, &exit_status);
	destroy_pipeline(&pipeline);
	return (try_decode_exit_status(exit_status, GENERAL_FAILURE));
}
