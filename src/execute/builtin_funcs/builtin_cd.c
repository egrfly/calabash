/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/27 22:31:32 by emflynn          ###   ########.fr       */
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
#include "../../interface/program_property_utils/program_property_utils.h"
#include "../../parse/parse.h"
#include "../execute.h"
#include "../var_utils/var_utils.h"

static void	print_var_or_usage_error(
				char *error_message)
{
	ft_dprintf(STDERR_FILENO, "%s: cd: %s\n", get_program_name(),
		error_message);
}

static bool	handle_cd_arguments(
				t_list_node **argument_node)
{
	if (*argument_node
		&& ft_strstarts((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "--"))
		return (print_var_or_usage_error("options not supported"), false);
	if (*argument_node
		&& !ft_strcmp((*argument_node)->value, "--"))
		*argument_node = (*argument_node)->next;
	if (*argument_node && (*argument_node)->next)
		return (print_var_or_usage_error("too many arguments"), false);
	return (true);
}

static bool	set_pwd_and_oldpwd_vars(
				char *previous_dir,
				t_list *vars,
				bool should_pwd)
{
	char	*current_dir;
	char	*new_pwd_var;
	char	*new_oldpwd_var;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (free(previous_dir), ft_dprintf(STDERR_FILENO,
				"%s: out of memory\n", get_program_name()), GENERAL_FAILURE);
	if (should_pwd)
		ft_printf("%s\n", current_dir);
	new_pwd_var = ft_strjoin("PWD=", current_dir);
	new_oldpwd_var = ft_strjoin("OLDPWD=", previous_dir);
	free(current_dir);
	free(previous_dir);
	if (!new_pwd_var || !new_oldpwd_var)
		return (free(new_pwd_var), free(new_oldpwd_var),
			ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), false);
	if (!upsert_var(new_pwd_var, vars, UNCHANGED_OR_EXPORTED)
		|| !upsert_var(new_oldpwd_var, vars, UNCHANGED_OR_EXPORTED))
		return (free(new_pwd_var), free(new_oldpwd_var), false);
	return (free(new_pwd_var), free(new_oldpwd_var), true);
}

static int	try_change_to_dir(
				const char *target_dir_path,
				t_list *vars,
				bool should_pwd)
{
	char	*current_dir;
	int		exit_status;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (ft_dprintf(STDERR_FILENO, "%s: out of memory\n",
				get_program_name()), GENERAL_FAILURE);
	if (!ft_strcmp(target_dir_path, ""))
		exit_status = SUCCESS;
	else
		exit_status = chdir(target_dir_path);
	if (exit_status != SUCCESS)
	{
		free(current_dir);
		return (ft_dprintf(STDERR_FILENO, "%s: cd: %s: %s\n",
				get_program_name(), target_dir_path, strerror(errno)),
			GENERAL_FAILURE);
	}
	if (!set_pwd_and_oldpwd_vars(current_dir, vars, should_pwd))
		return (GENERAL_FAILURE);
	return (SUCCESS);
}

int	builtin_cd(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	bool						should_pwd;
	char						*target_dir_path;

	((void)tokens_and_syntax_tree, node_value = node->value);
	argument_node = node_value->arguments->first->next;
	should_pwd = false;
	if (!handle_cd_arguments(&argument_node))
		return (GENERAL_FAILURE);
	else if (argument_node && !ft_strcmp(argument_node->value, "-")
		&& get_var_value("OLDPWD", program_vars->vars))
	{
		target_dir_path = get_var_value("OLDPWD", program_vars->vars);
		should_pwd = true;
	}
	else if (argument_node && !ft_strcmp(argument_node->value, "-"))
		return (print_var_or_usage_error("OLDPWD not set"), GENERAL_FAILURE);
	else if (argument_node)
		target_dir_path = argument_node->value;
	else if (get_var_value("HOME", program_vars->vars))
		target_dir_path = get_var_value("HOME", program_vars->vars);
	else
		return (print_var_or_usage_error("HOME not set"), GENERAL_FAILURE);
	return (try_change_to_dir(target_dir_path, program_vars->vars, should_pwd));
}
