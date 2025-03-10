/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 04:22:48 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 15:02:13 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_binary_tree.h"
#include "ft_list.h"
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../../interface/option_utils/option_utils.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../../parse/parse.h"
#include "../../parse/word_utils/word_utils.h"
#include "../execute.h"
#include "../builtin_utils/builtin_utils.h"
#include "../var_utils/var_utils.h"

static bool	handle_export_options(
				t_list_node **argument_node,
				t_export_mode *mode)
{
	while (*argument_node
		&& is_option_sequence_consisting_of_chars(
			(*argument_node)->value, "n"))
	{
		*mode = NOT_EXPORTED;
		*argument_node = (*argument_node)->next;
	}
	if (*argument_node
		&& ft_strstarts((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "-")
		&& ft_strcmp((*argument_node)->value, "--"))
		return (false);
	if (*argument_node
		&& !ft_strcmp((*argument_node)->value, "--"))
		*argument_node = (*argument_node)->next;
	return (true);
}

static void	print_with_escape_chars(
				char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("$`\\\"", str[i]))
			ft_printf("\\");
		ft_printf("%c", str[i]);
		i++;
	}
}

static void	print_var_declarations(
				t_list *vars)
{
	t_list_node	*current_var_node;
	char		*current_var;
	char		*equals_sign;
	size_t		var_name_length;

	current_var_node = vars->first;
	while (current_var_node)
	{
		current_var = current_var_node->value;
		var_name_length = ft_strcspn(current_var, "=");
		if (!ft_strstarts(current_var, NOT_EXPORTED_PREFIX))
		{
			ft_printf("declare -x %.*s", var_name_length, current_var);
			equals_sign = ft_strchr(current_var, '=');
			if (equals_sign)
			{
				ft_printf("=\"");
				print_with_escape_chars(&equals_sign[1]);
				ft_printf("\"\n");
			}
		}
		current_var_node = current_var_node->next;
	}
}

int	builtin_export(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	t_export_mode				mode;
	int							exit_status;

	(void)tokens_and_syntax_tree;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	mode = EXPORTED;
	if (!handle_export_options(&argument_node, &mode))
		return (ft_dprintf(STDERR_FILENO, "%s: unset: %s\n",
				get_program_name(), "options not supported"),
			GENERAL_FAILURE);
	if (!argument_node)
		return (print_var_declarations(program_vars->vars), SUCCESS);
	exit_status = SUCCESS;
	while (argument_node)
	{
		if (!upsert_var(argument_node->value, program_vars->vars, mode))
			exit_status = GENERAL_FAILURE;
		argument_node = argument_node->next;
	}
	return (exit_status);
}
