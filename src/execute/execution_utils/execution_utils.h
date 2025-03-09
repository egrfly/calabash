/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:18:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 17:14:01 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

int		execute_in_child_process(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_fixed_program_elements *fixed_program_elements,
			t_program_vars *program_vars);
void	destroy_fixed_program_elements(
			t_fixed_program_elements *fixed_program_elements);

int		try_decode_exit_status(
			int exit_status,
			int alternative_exit_status);

#endif
