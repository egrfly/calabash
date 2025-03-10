/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/10 10:05:34 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../variable_utils/variable_utils.h"

static int	print_usage_or_environment_error(
				char *error_message)
{
	return (ft_dprintf(STDERR_FILENO, "%s: cd: %s\n", get_program_name(),
			error_message), GENERAL_FAILURE);
}

// TODO: consider memory when using env
// TODO: update PWD and OLDPWD when using env
static int	try_change_to_dir(
				const char *target_dir_path,
				char **oldpwd)
{
	char	*current_dir;
	int		exit_status;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), GENERAL_FAILURE);
	exit_status = chdir(target_dir_path);
	*oldpwd = current_dir;
	if (exit_status != SUCCESS)
		return (ft_dprintf(STDERR_FILENO, "%s: cd: %s: %s\n",
				get_program_name(), target_dir_path, strerror(errno)),
			GENERAL_FAILURE);
	return (SUCCESS);
}

// TODO: change OLDPWD to use env
int	builtin_cd(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	static char					*oldpwd = NULL;
	char						*home_dir;
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	char						*target_dir_path;

	(void)tokens_and_syntax_tree;
	home_dir = get_variable_value(program_vars->env, "HOME");
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	if (argument_node && argument_node->next)
		return (print_usage_or_environment_error("too many arguments"));
	else if (argument_node && !ft_strcmp(argument_node->value, "-") && oldpwd)
		target_dir_path = oldpwd;
	else if (argument_node && !ft_strcmp(argument_node->value, "-"))
		return (print_usage_or_environment_error("OLDPWD not set"));
	else if (argument_node)
		target_dir_path = argument_node->value;
	else if (home_dir)
		target_dir_path = home_dir;
	else
		return (print_usage_or_environment_error("HOME not set"));
	return (try_change_to_dir(target_dir_path, &oldpwd));
}
