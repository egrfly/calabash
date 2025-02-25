/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:48:53 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/25 12:17:24 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "ft_list.h"
#include "../../interface/interface.h"
#include "../lex.h"
#include "../input_utils/input_utils.h"
#include "../token_utils/token_utils.h"

bool	handle_comment(
			t_input_tracker *input_tracker,
			t_tokens_with_status *tokens_with_status,
			t_multiline_options *multiline_options)
{
	(void)multiline_options;
	if (get_current_char(input_tracker) == '#')
	{
		delimit_last_token_if_exists(
			input_tracker,
			get_last_token(tokens_with_status->tokens),
			&tokens_with_status->out_of_memory);
		if (tokens_with_status->out_of_memory)
			return (false);
		while (get_current_char(input_tracker)
			&& get_current_char(input_tracker) != '\n')
			input_tracker->index_in_line++;
		return (true);
	}
	return (false);
}
