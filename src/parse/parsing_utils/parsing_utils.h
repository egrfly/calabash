/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:44:19 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 18:06:11 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include "ft_list.h"
# include "../../interface/interface.h"
# include "../parse.h"

typedef struct s_parsing_tracker
{
	t_list_node			*checkpoint;
	t_list_node			*current_token_node;
	int					tokens_consumed_count;
	int					tokens_consumed_this_step_count;
	int					step_index;
	t_parsing_option	step;
}	t_parsing_tracker;

int	parse_recursively(
		t_list_node **first_token_node,
		t_syntax_tree *syntax_tree,
		t_multiline_options *multiline_options,
		const t_parsing_option_sequence_with_count **parsing_option_sequences);

#endif
