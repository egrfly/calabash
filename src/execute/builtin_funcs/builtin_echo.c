/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 04:09:55 by aistok            #+#    #+#             */
/*   Updated: 2025/03/10 10:19:45 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_stdio.h"
#include "ft_string.h"
#include "../../main.h"
#include "../../interface/program_name_utils/program_name_utils.h"
#include "../execution_funcs/execution_funcs.h"

static bool	is_dash_n_sequence(const char *argument)
{
	size_t	i;

	if (ft_strstarts(argument, "-n"))
	{
		i = ft_strlen("-n");
		while (argument[i] && argument[i] == 'n')
			i++;
		if (!argument[i])
			return (true);
	}
	return (false);
}

static bool	is_unsupported_option_sequence(const char *argument)
{
	bool	contains_unsupported_option;
	size_t	i;

	if (ft_strstarts(argument, "-n")
		|| ft_strstarts(argument, "-e")
		|| ft_strstarts(argument, "-E"))
	{
		contains_unsupported_option = false;
		i = 1;
		while (argument[i] && ft_strchr("neE", argument[i]))
		{
			if (ft_strchr("eE", argument[i]))
				contains_unsupported_option = true;
			i++;
		}
		if (!argument[i])
			return (contains_unsupported_option);
	}
	return (false);
}

static bool	handle_echo_options(
				t_list_node **argument_node,
				bool *print_last_newline)
{
	while (*argument_node
		&& is_dash_n_sequence((*argument_node)->value))
	{
		*print_last_newline = false;
		*argument_node = (*argument_node)->next;
	}
	if (*argument_node
		&& is_unsupported_option_sequence((*argument_node)->value))
		return (false);
	if (*argument_node
		&& !ft_strcmp((*argument_node)->value, "--"))
		*argument_node = (*argument_node)->next;
	return (true);
}

int	builtin_echo(
		t_binary_tree_node *node,
		t_tokens_and_syntax_tree *tokens_and_syntax_tree,
		t_program_vars *program_vars)
{
	t_syntax_tree_node_value	*node_value;
	t_list_node					*argument_node;
	bool						print_last_newline;

	(void)tokens_and_syntax_tree;
	(void)program_vars;
	node_value = node->value;
	argument_node = node_value->arguments->first->next;
	print_last_newline = true;
	if (!handle_echo_options(&argument_node, &print_last_newline))
		return (ft_dprintf(STDERR_FILENO, "%s: echo: %s\n", get_program_name(),
				"options other than -n not supported"), GENERAL_FAILURE);
	while (argument_node)
	{
		ft_printf("%s", argument_node->value);
		if (argument_node->next)
			ft_printf(" ");
		argument_node = argument_node->next;
	}
	if (print_last_newline)
		ft_printf("\n");
	return (SUCCESS);
}
