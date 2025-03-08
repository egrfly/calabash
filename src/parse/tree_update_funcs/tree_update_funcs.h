/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_update_funcs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 04:43:32 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 14:43:43 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UPDATE_FUNCS_H
# define TREE_UPDATE_FUNCS_H

# include <stdbool.h>
# include "ft_list.h"
# include "../parse.h"

bool	update_by_moving_current_node_up_to_control_structure_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_by_moving_current_node_up_to_function_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_with_new_function(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_coprocess_to_use_custom_identifier(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_time_command_to_use_posix_option(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_assignment(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_argument(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_left_number(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_left_redirection_word(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_operator(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_right_dash(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_right_number_dash(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_right_number(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_with_new_redirection_right_word(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_redirection_if_here_doc_or_string(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_command_to_terminated(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_with_new_pre_command_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_with_new_mid_or_post_command_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);
bool	update_by_closing_previous_pre_command_node(
			t_syntax_tree *syntax_tree,
			t_list_node *current_token_node);

#endif
