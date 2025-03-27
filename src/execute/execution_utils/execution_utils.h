/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:18:29 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/19 17:52:42 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_UTILS_H
# define EXECUTION_UTILS_H

# include "ft_binary_tree.h"
# include "../../interface/interface.h"
# include "../execute.h"

int		create_child_process_and_execute(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_program_vars *program_vars);
void	execute_and_exit(
			t_execution_func execution_func,
			t_binary_tree_node *node,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree,
			t_program_vars *program_vars);
void	execute_external_command(
			int pipe_fd[2],
			char **argv,
			t_program_vars *program_vars,
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);
void	destroy_tokens_and_syntax_tree(
			t_tokens_and_syntax_tree *tokens_and_syntax_tree);
int		try_decode_exit_status(
			int exit_status,
			int backup_exit_status);
int		update_last_exit_status(
			int exit_status,
			t_program_vars *program_vars);

#endif
