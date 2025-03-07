/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:31:37 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/07 09:41:35 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../../lex/lex.h"
#include "../../parse/parse.h"
#include "../redirection_funcs/redirection_funcs.h"

static const
	t_redirection_func
	g_redirection_funcs[] = {
[AMPERSAND_GREATER_GREATER] = NULL,
[AMPERSAND_GREATER] = NULL,
[LESS_LESS_LESS] = NULL,
[LESS_LESS_DASH] = NULL,
[LESS_LESS] = NULL,
[LESS_GREATER] = NULL,
[LESS_AMPERSAND] = NULL,
[LESS] = NULL,
[GREATER_GREATER] = NULL,
[GREATER_BAR] = NULL,
[GREATER_AMPERSAND] = NULL,
[GREATER] = perform_write_redirection,
};

static int	perform_redirection(
				t_redirection *redirection,
				char *program_name)
{
	t_redirection_func	redirection_func;

	redirection_func = g_redirection_funcs[redirection->operator];
	if (redirection_func)
		return (redirection_func(redirection, program_name));
	return (GENERAL_FAILURE);
}

int	perform_redirections(
		t_list *redirections,
		char *program_name)
{
	int				exit_status;
	t_list_node		*current_redirection_node;
	t_redirection	*current_redirection;

	exit_status = SUCCESS;
	current_redirection_node = redirections->first;
	while (current_redirection_node)
	{
		current_redirection = current_redirection_node->value;
		exit_status = perform_redirection(current_redirection, program_name);
		if (exit_status != SUCCESS)
			return (exit_status);
		current_redirection_node = current_redirection_node->next;
	}
	return (exit_status);
}
