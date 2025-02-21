/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_node_lifecycle.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:23:58 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/18 19:15:07 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_NODE_LIFECYCLE_H
# define TREE_NODE_LIFECYCLE_H

# include "ft_binary_tree.h"

t_binary_tree_node	*create_syntax_tree_node(
						t_syntax_tree_node_value_type type);
void				destroy_syntax_tree_node(
						t_binary_tree_node *node);

#endif
