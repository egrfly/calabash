/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:47:20 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 22:19:05 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_stdio.h"
#include "../../interface/interface.h"
#include "../execute.h"
#include "../execution_utils/execution_utils.h"
#include "../list_utils/list_utils.h"
#include "../path_utils/path_utils.h"

static void	exit_if_out_of_memory(
				char *program_name,
				char **arguments,
				char **envp,
				char *command_path)
{
	ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
		program_name);
	free(arguments);
	free(envp);
	free(command_path);
	exit(GENERAL_FAILURE);
}

static void	exit_if_command_not_found(
				char *program_name,
				char *unfound_command,
				char **arguments,
				char **envp)
{
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name, unfound_command,
		"command not found");
	free(arguments);
	free(envp);
	exit(NOT_FOUND);
}

static void	exit_if_execve_failed(
				char *program_name,
				char *command,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	int	exit_status;

	if (errno == ENOENT)
		exit_status = NOT_FOUND;
	else if (errno == EACCES)
		exit_status = COULD_NOT_EXECUTE;
	else
		exit_status = GENERAL_FAILURE;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name, command,
		strerror(errno));
	destroy_tokens_and_syntax_tree(tokens_and_syntax_tree);
	exit(exit_status);
}

static int	locate_and_execute_command(
				t_binary_tree_node *node,
				t_tokens_and_syntax_tree *tokens_and_syntax_tree,
				t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	char						**arguments;
	char						**envp;
	char						*command_path;

	node_value = node->value;
	arguments = get_values_from_list(node_value->arguments);
	envp = get_values_from_list(program_name_and_env->env);
	command_path = NULL;
	if (!arguments || !envp || !get_full_command_path(&command_path,
			node_value->arguments->first->value,
			get_path_variable(program_name_and_env->env)))
		exit_if_out_of_memory(program_name_and_env->name, arguments, envp,
			command_path);
	if (!command_path)
		exit_if_command_not_found(program_name_and_env->name,
			node_value->arguments->first->value, arguments, envp);
	execve(command_path, arguments, envp);
	free(arguments);
	free(envp);
	free(command_path);
	exit_if_execve_failed(program_name_and_env->name,
		node_value->arguments->first->value, tokens_and_syntax_tree);
	return (GENERAL_FAILURE);
}

// TODO: figure out what to do in the case of assignments and redirections only
int	execute_simple_command(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_name_and_env *program_name_and_env)
{
	t_syntax_tree_node_value	*node_value;
	t_syntax_tree_node_value	*parent_node_value;

	node_value = node->value;
	if (node_value->arguments->first)
	{
		if (node->parent)
		{
			parent_node_value = node->parent->value;
			if (parent_node_value->type == PIPE)
				return (locate_and_execute_command(node,
						tokens_and_syntax_tree, program_name_and_env));
		}
		return (execute_in_child_process(locate_and_execute_command, node,
				tokens_and_syntax_tree, program_name_and_env));
	}
	return (SUCCESS);
}
