/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_escaped_section.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:16:04 by emflynn           #+#    #+#             */
/*   Updated: 2025/02/11 20:13:58 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../lex.h"

bool	in_escaped_section(
			t_input_tracker *input_tracker)
{
	return (input_tracker->quote_mode == ESCAPED
		|| input_tracker->quote_mode == DOUBLE_QUOTED_AND_ESCAPED);
}
