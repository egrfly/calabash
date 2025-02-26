/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:09:07 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/26 14:23:00 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_NODE_UTILS_H
# define TREE_NODE_UTILS_H

# include "../../lex/lex.h"
# include "../parse.h"

# define OTHER_COMMAND 0

t_syntax_tree_node_value_type	get_node_type_from_token(
									t_token *token);
bool							node_is_of_a_single_child_type(
									t_syntax_tree_node_value *node_value);
bool							node_is_of_a_double_child_type(
									t_syntax_tree_node_value *node_value);
bool							node_is_of_a_control_structure_type(
									t_syntax_tree_node_value *node_value);
bool							node_is_of_type_simple_command(
									t_syntax_tree_node_value *node_value);
bool							node_is_of_type_simple_or_shell_command(
									t_syntax_tree_node_value *node_value);
bool							node_is_of_type_function(
									t_syntax_tree_node_value *node_value);
bool							node_is_of_type(
									t_syntax_tree_node_value *node_value,
									t_syntax_tree_node_value_type type);
bool							node_is_primary_child_of_parent(
									t_binary_tree_node *node);
bool							node_is_secondary_child_of_parent(
									t_binary_tree_node *node);
bool							node_is_terminated(
									t_syntax_tree_node_value *node_value);

#endif
