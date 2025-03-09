/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_fixed_program_elements.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:05:15 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/09 19:44:49 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_list.h"
#include "../../lex/token_lifecycle/token_lifecycle.h"
#include "../../interface/line_getters/line_getters.h"
#include "../../interface/line_utils/line_utils.h"
#include "../../parse/tree_lifecycle/tree_lifecycle.h"
#include "../execute.h"
#include "../pipeline_lifecycle/pipeline_lifecycle.h"

void	destroy_fixed_program_elements(
			t_fixed_program_elements *fixed_program_elements)
{
	int	fd;

	ft_list_destroy(fixed_program_elements->tokens,
		(t_action_func)destroy_token);
	destroy_syntax_tree(fixed_program_elements->syntax_tree);
	if (fixed_program_elements->multiline_options->get_next_line
		== noninteractive_get_next_line_from_split_string)
	{
		discard_remaining_lines_if_present(
			fixed_program_elements
			->multiline_options);
	}
	else if (fixed_program_elements->multiline_options->get_next_line
		== noninteractive_get_next_line_from_file_descriptor)
	{
		fd = *(int *)fixed_program_elements
			->multiline_options
			->get_next_line_arg;
		close(fd);
	}
}
