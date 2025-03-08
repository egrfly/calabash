/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:31:37 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 08:15:09 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../../parse/parse.h"
#include "../redirection_funcs/redirection_funcs.h"
#include "./redirection_utils.h"

static const
	t_redirection_func
	g_redirection_funcs[] = {
[AMPERSAND_GREATER_GREATER] = perform_append_both_redirection,
[AMPERSAND_GREATER] = perform_write_both_redirection,
[LESS_LESS_LESS] = NULL,
[LESS_LESS_DASH] = NULL,
[LESS_LESS] = NULL,
[LESS_GREATER] = perform_read_write_redirection,
[LESS_AMPERSAND] = perform_input_duplication,
[LESS] = perform_read_redirection,
[GREATER_GREATER] = perform_append_redirection,
[GREATER_BAR] = perform_write_redirection,
[GREATER_AMPERSAND] = perform_output_duplication,
[GREATER] = perform_write_redirection,
};

static bool	perform_redirection(
				t_redirection *redirection,
				char *program_name)
{
	t_redirection_func	redirection_func;

	redirection_func = g_redirection_funcs[redirection->operator];
	if (redirection_func)
		return (redirection_func(redirection, program_name));
	return (false);
}

bool	perform_redirections(
			t_list *redirections,
			char *program_name)
{
	t_list_node		*current_redirection_node;
	t_redirection	*current_redirection;

	current_redirection_node = redirections->first;
	while (current_redirection_node)
	{
		current_redirection = current_redirection_node->value;
		if (!perform_redirection(current_redirection, program_name))
		{
			revert_redirections(redirections);
			return (false);
		}
		current_redirection_node = current_redirection_node->next;
	}
	return (true);
}
