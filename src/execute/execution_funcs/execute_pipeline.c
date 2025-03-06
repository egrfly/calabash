/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:57:01 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 02:09:03 by emflynn          ###   ########.fr       */
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
#include "../../interface/interface.h"
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

static int	execute_section_of_pipeline(
				t_pipeline *pipeline,
				t_program_name_and_env *program_name_and_env,
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	pipeline->pids[pipeline->current_index] = fork();
	if (pipeline->pids[pipeline->current_index] < 0)
	{
		close_pipe_fds_for_process(pipeline->pipe_fds, pipeline->pipe_count);
		destroy_pipeline(pipeline);
		return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name_and_env
				->name, "cannot fork", strerror(errno)), GENERAL_FAILURE);
	}
	if (pipeline->pids[pipeline->current_index] == 0)
	{
		if (pipeline->current_index < pipeline->pipe_count)
			dup2(pipeline->pipe_fds[pipeline->current_index][READ_END],
				STDIN_FILENO);
		if (pipeline->current_index > 0)
			dup2(pipeline->pipe_fds[pipeline->current_index - 1][WRITE_END],
				STDOUT_FILENO);
		close_pipe_fds_for_process(pipeline->pipe_fds, pipeline->pipe_count);
		execute_recursively(select_correct_child_to_execute(node,
				pipeline->current_index == pipeline->pipe_count),
			tokens_and_syntax_tree, program_name_and_env);
		destroy_pipeline(pipeline);
		destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
		exit(GENERAL_FAILURE);
	}
	return (SUCCESS);
}

// TODO: look into macros like WIFEXITED, WEXITSTATUS, WIFSIGNALED etc.
int	execute_pipeline(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	int					exit_status;
	t_pipeline			pipeline;

	exit_status = init_pipeline(&pipeline,
			count_pipes_in_current_pipeline(node), program_name_and_env->name);
	if (exit_status != SUCCESS)
		return (exit_status);
	pipeline.current_index = 0;
	while (pipeline.current_index <= pipeline.pipe_count)
	{
		exit_status = execute_section_of_pipeline(&pipeline,
				program_name_and_env, node, tokens_and_syntax_tree);
		if (exit_status != SUCCESS)
			return (exit_status);
		pipeline.current_index++;
		if (pipeline.current_index < pipeline.pipe_count)
			node = node->primary_child;
	}
	close_pipe_fds_for_process(pipeline.pipe_fds, pipeline.pipe_count);
	while (wait(&exit_status) > 0)
		;
	destroy_pipeline(&pipeline);
	return (exit_status);
}
