/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_char_pointer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emflynn <emflynn@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:54:00 by emflynn           #+#    #+#             */
/*   Updated: 2025/03/10 06:52:50 by emflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lex.h"

char	*get_current_char_pointer(
			t_input_tracker *input_tracker)
{
	return (&input_tracker->current_input_line[
			input_tracker->index_in_line]);
}
