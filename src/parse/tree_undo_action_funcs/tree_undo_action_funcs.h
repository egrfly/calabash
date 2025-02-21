/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_undo_action_funcs.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 00:07:51 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/20 22:16:37 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UNDO_ACTION_FUNCS_H
# define TREE_UNDO_ACTION_FUNCS_H

# include "../parse.h"

void	undo_set_current_command_to_terminated(
			t_syntax_tree *syntax_tree);
void	undo_create_assignment(
			t_syntax_tree *syntax_tree);
void	undo_create_argument(
			t_syntax_tree *syntax_tree);
void	undo_create_redirection(
			t_syntax_tree *syntax_tree);
void	undo_set_redirection_left_number(
			t_syntax_tree *syntax_tree);
void	undo_set_redirection_left_redirection_word(
			t_syntax_tree *syntax_tree);
void	undo_set_redirection_operator(
			t_syntax_tree *syntax_tree);
void	undo_set_redirection_right_dash(
			t_syntax_tree *syntax_tree);
void	undo_set_redirection_right_number(
			t_syntax_tree *syntax_tree);
void	undo_set_redirection_right_word(
			t_syntax_tree *syntax_tree);
void	undo_set_time_posix_option(
			t_syntax_tree *syntax_tree);
void	undo_set_coprocess_custom_identifier(
			t_syntax_tree *syntax_tree);
void	undo_set_function_identifier(
			t_syntax_tree *syntax_tree);
void	undo_set_tree_root_to_new_tree_root_parent(
			t_syntax_tree *syntax_tree);
void	undo_set_tree_root_and_current_node_to_new_non_null_node(
			t_syntax_tree *syntax_tree);
void	undo_set_current_node_to_new_non_null_primary_child(
			t_syntax_tree *syntax_tree);
void	undo_set_current_node_to_new_non_null_secondary_child(
			t_syntax_tree *syntax_tree);
void	undo_set_current_node_from_parent_to_child(
			t_syntax_tree *syntax_tree);
void	undo_set_current_node_from_primary_child_to_parent(
			t_syntax_tree *syntax_tree);
void	undo_set_current_node_from_secondary_child_to_parent(
			t_syntax_tree *syntax_tree);
void	undo_set_current_node_to_new_secondary_child_sibling(
			t_syntax_tree *syntax_tree);
void	undo_slot_new_node_between_current_primary_child_and_parent(
			t_syntax_tree *syntax_tree);
void	undo_slot_new_node_between_current_secondary_child_and_parent(
			t_syntax_tree *syntax_tree);

#endif
