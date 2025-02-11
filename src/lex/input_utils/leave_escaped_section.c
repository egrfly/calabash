/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_escaped_section.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:16:06 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 20:13:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lex.h"

void	leave_escaped_section(
			t_input_tracker *input_tracker)
{
	if (input_tracker->quote_mode == ESCAPED)
		input_tracker->quote_mode = UNQUOTED;
	if (input_tracker->quote_mode == DOUBLE_QUOTED_AND_ESCAPED)
		input_tracker->quote_mode = DOUBLE_QUOTED;
}
