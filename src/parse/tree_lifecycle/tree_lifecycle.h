/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_lifecycle.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:54:11 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/21 07:01:03 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_LIFECYCLE_H
# define TREE_LIFECYCLE_H

# include "ft_list.h"
# include "../parse.h"

# define BEGINNING 0

t_syntax_tree	*create_syntax_tree(void);
void			deconstruct_syntax_tree_back_to_checkpoint(
					t_syntax_tree *syntax_tree,
					t_list_node *checkpoint);
void			destroy_syntax_tree(t_syntax_tree *syntax_tree);

#endif
