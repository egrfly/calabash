/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens_and_syntax_tree.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:05:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/05 22:25:46 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../lex/tokens_with_status_lifecycle/tokens_with_status_lifecycle.h"
#include "../../interface/line_getters/line_getters.h"
#include "../../interface/line_utils/line_utils.h"
#include "../../parse/tree_lifecycle/tree_lifecycle.h"
#include "../execute.h"

void	destroy_tokens_and_syntax_tree(
			t_tokens_and_syntax_tree *tokens_and_syntax_tree)
{
	int	fd;

	destroy_tokens_with_status(tokens_and_syntax_tree->tokens_with_status);
	destroy_syntax_tree(tokens_and_syntax_tree->syntax_tree);
	if (tokens_and_syntax_tree->multiline_options->get_next_line
		== noninteractive_get_next_line_from_split_string)
	{
		discard_remaining_lines_if_present(
			tokens_and_syntax_tree
			->multiline_options);
	}
	else if (tokens_and_syntax_tree->multiline_options->get_next_line
		== noninteractive_get_next_line_from_file_descriptor)
	{
		fd = *(int *)tokens_and_syntax_tree
			->multiline_options
			->get_next_line_arg;
		close(fd);
	}
}
