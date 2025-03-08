/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:18:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 09:03:56 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

# define NO_OPTIONS 0

# define FORK_FAILURE -1
# define CHILD_PROCESS_ID 0

int		execute_in_child_process(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_fixed_program_elements *fixed_program_elements,
			t_program_vars *program_vars);
void	destroy_fixed_program_elements(
			t_fixed_program_elements *fixed_program_elements);

#endif
