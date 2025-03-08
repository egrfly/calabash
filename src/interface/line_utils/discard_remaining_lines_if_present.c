/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_remaining_lines_if_present.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 01:40:33 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/08 16:04:12 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
#include "../interface.h"
#include "../line_getters/line_getters.h"

void	discard_remaining_lines_if_present(
			t_multiline_options *multiline_options)
{
	if (multiline_options->get_next_line
		== noninteractive_get_next_line_from_split_string)
		access_input_lines(DELETE, NO_ARG);
}
