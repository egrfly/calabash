/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 04:08:02 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/18 15:51:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "ft_binary_tree.h"
# include "ft_list.h"
# include "../lex/lex.h"

# define BASE_LEVEL 0

char	*get_operator_symbol(t_operator operator);
void	print_tokens(t_list *tokens);
void	print_syntax_tree(t_binary_tree *tree);

#endif
