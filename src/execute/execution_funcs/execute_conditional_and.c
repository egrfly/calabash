/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_conditional_and.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:22:18 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:00:14 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binary_tree.h"
#include "../../main.h"
#include "../../interface/interface.h"
#include "../execute.h"

int	execute_conditional_and(
		t_binary_tree_node *node,
		t_fixed_program_elements *fixed_program_elements,
		t_program_vars *program_vars)
{
	int	exit_status;

	exit_status = execute_recursively(node->primary_child,
			fixed_program_elements, program_vars);
	if (exit_status == SUCCESS)
		exit_status = execute_recursively(node->secondary_child,
				fixed_program_elements, program_vars);
	return (exit_status);
}
