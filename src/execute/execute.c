/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:40:47 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/06 15:39:43 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "ft_stdlib.h"
#include "ft_string.h"
#include "../interface/interface.h"
#include "../parse/parse.h"
#include "./signals/signals.h"
#include "./builtins/builtins.h"
#include "./execute.h"

static char	**get_arguments_from_list(t_list *arguments_list)
{
	char		**arguments;
	t_list_node	*current_argument_node;
	size_t		i;

	arguments = ft_calloc(arguments_list->size + 1, sizeof(char *));
	if (!arguments)
		return (NULL);
	current_argument_node = arguments_list->first;
	i = 0;
	while (i < arguments_list->size)
	{
		arguments[i] = current_argument_node->value;
		current_argument_node = current_argument_node->next;
		i++;
	}
	return (arguments);
}

/*
 *	NOTE: this function is executed in a child process, hence
 *	the exit at the end ONLY EXITS the child process!
 */
static int	execute_external_command(
				t_syntax_tree_node_value *node_value,
				char *program_name, char **envp)
{
	char	**arguments;
	int		return_value;

	arguments = get_arguments_from_list(node_value->arguments);
	if (!arguments)
		return (GENERAL_FAILURE);
	execve(node_value->arguments->first->value, arguments, envp);
	free(arguments);
	if (errno == ENOENT)
		return_value = NOT_FOUND;
	else if (errno == EACCES)
		return_value = COULD_NOT_EXECUTE;
	else
		return_value = GENERAL_FAILURE;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", program_name,
		node_value->arguments->first->value, strerror(errno));
	exit(return_value);
}

/* NORMINETTE: function too long! */
static int	execute_simple_command(
	t_syntax_tree_node_value *node_value,
	char *program_name, char **envp, int *status)
{
	char	**arguments;
	pid_t	pid;

	*status = SUCCESS;
	arguments = get_arguments_from_list(node_value->arguments);
	if (is_builtin_command(node_value->arguments->first->value))
	{
		*status = execute_builtin_command(
				node_value->arguments->first->value, arguments, envp);
		free(arguments);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			*status = GENERAL_FAILURE;
		else if (pid == 0)
		{
			*status
				= execute_external_command(node_value, program_name, envp);
			exit(*status);
		}
		else
		{
			waitpid(pid, status, 0);
			if (g_signal == SIGNAL_FOR_CTRL_C)
				*status = CTRL_C_TERMINATED;
			if (g_signal == SIGNAL_FOR_CTRL_BACKSLASH)
				*status = CTRL_BACKSLASH_TERMINATED;
		}
	}
	return (*status);
}

static int	execute_recursively(
				t_binary_tree_node *node,
				char *program_name, char **envp, int *status)
{
	t_syntax_tree_node_value	*node_value;

	if (!node)
		return (SUCCESS);
	node_value = node->value;
	if (node_value->type == SIMPLE_COMMAND)
	{
		if (node_value->arguments->first)
			return (execute_simple_command(node_value,
					program_name, envp, status));
	}
	return (SUCCESS);
}

int	execute(
		t_binary_tree *tree, char *program_name, char **envp)
{
	int	status;

	status = SUCCESS;
	return (execute_recursively(tree->root, program_name, envp, &status));
}
